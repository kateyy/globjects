

#include <string>
#include <cmath>
#include <iostream>

// [BEGIN] Includes of GLOW
#include <glow/Buffer.h>
#include <glow/Error.h>
#include <glow/debugmessageoutput.h>
#include <glow/Program.h>
#include <glow/Shader.h>
#include <glow/String.h>
#include <glow/Uniform.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
// [END] Includes of GLOW

// [BEGIN] Includes of GLOWUTILS
#include <glowutils/StringTemplate.h>
#include <glowutils/Timer.h>
#include <glowutils/global.h>
// [END] Includes of GLOWUTILS

// [BEGIN] Includes of GLOWWINDOW
#include <glowwindow/Context.h>
#include <glowwindow/WindowEventHandler.h>
#include <glowwindow/Window.h>
// [END] Includes of GLOWWINDOW





/**
 * Ananonymous namespace in which the vertex and fragment shader source code is declared and initialized
 * as well as the float array that maintains the raw vertex positions of the triangle to draw.
 */
namespace {
    /**
     * The vertex positions of the triangle to draw (in clip-space).
     */
    const float vertexPositions[] {
        0.25f, 0.25f, 0.0f, 1.0f,
        0.25f, -0.25f, 0.0f, 1.0f,
        -0.25f, -0.25f, 0.0f, 1.0f
    };
}



/**
 *
 */
class EventHandler : public glowwindow::WindowEventHandler {
    
// [BEGIN] :: public
public:
    
    /**
     * Default "do nothing" c'tor.
     */
	EventHandler() { /* do nothing*/ }

    /**
     * Default "do nothing" destructor.
     */
    virtual ~EventHandler() { /* do nothing*/ }
    
    /**
     * Initializes the shader program and the vertex buffer that stores the data of the geometry to be
     * rendered.
     *
     * This method corresponds to function tut1.cpp::init() -- that in turn calls function InitializePorgram()
     * and InitializeVertexBuffer() -- in the original source code of the tutorial.
     */
    virtual void initialize(glowwindow::Window& /*window*/) override {
        
        // enable context specific debug message output (don't bother ;)).
        glow::debugmessageoutput::enable();
        
        // create the timer
        timer = new glowutils::Timer();
        
        // cf. protected methods for implementation of "initializeProgram()" and "initializeVertexBuffer()"
        initializeProgram();
        initializeVertexBuffer();
        
        /*
         * Create the vertex array object and bind it
         *
         * original source snippet:
         *
         *      	glGenBuffers(1, &positionBufferObject);
         *          glBindVertexArray(vao);
         */
		vao = new glow::VertexArrayObject();
        vao->bind();

    }
    
    /**
     * This callback is used to update the viewport whenever a "ResizeEvent" is triggered and
     * corresponds to function tut1.cpp::reshape()
     */
    virtual void framebufferResizeEvent(glowwindow::ResizeEvent& event) override {
        /**
         * Resizes the viewport without maintaining the aspect ratio of the window, thus,
         * possibly deforming the rendered geometry.
         */
        glViewport(0, 0, event.width(), event.height());
        CheckGLError();
    }
    
    /**
     * This method implements the rendering code of this tutorial.
     *
     * This method is a callback to handle `glowwindow::PaintEvent`s and corresponds to the
     * original tutorial's `cpuPositionsOffset.cpp::display()` function.
     *
     * The original function source code is as follows:
     *
     *      void display() {
     *
     *          float fXOffset = 0.0f, fYOffset = 0.0f;
     *          ComputePositionOffsets(fXOffset, fYOffset);
     *          AdjustVertexData(fXOffset, fYOffset);
     *
     *          glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
     *          glClear(GL_COLOR_BUFFER_BIT);
     *
     *          glUseProgram(theProgram);
     *
     *          glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
     *          glEnableVertexAttribArray(0);
     *          glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
     *
     *          glDrawArrays(GL_TRIANGLES, 0, 3);
     *
     *          glDisableVertexAttribArray(0);
     *          glUseProgram(0);
     *
     *          glutSwapBuffers();
     *          glutPostRedisplay();
     *      }
     *
     * Note, the function call "glutSwapBuffers()" is a call of a freeglut function. As this tutorial
     * does not use freeglut this function call is not to be found in this method!
     */
    virtual void paintEvent(glowwindow::PaintEvent &) override {

        /*
         * Compute the new x-/y-offset according to the elapsed time and adjust the x-/y-coordinates
         * of the geometry by adding the new x-/y-offset.
         */
        float xOffset {0.0};
        float yOffset {0.0};
        
        computePositionOffset(xOffset, yOffset);

        
        
        // set color to clear the screen, check for an OpenGL error, actually
        // clear the screen and check for an OpenGL error again.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        CheckGLError();
        
        glClear(GL_COLOR_BUFFER_BIT);
        CheckGLError();
        
        /*
         * Set the shader program to use by the subsequent rendering commands. The plain OpenGL
         * function call encapsulated by program->use() is glUseProgram(GLuint theProgram).
         *
         * Original tutorial source snippet:
         * 
         *      glUseProgram(theProgram);
         *
         * As member theProgram is a glow::Program object theProgram-id() must be used to obtain
         * the GLuint that identifies the program.
         */
		theProgram->use();
//        glUseProgram(theProgram->id());
//        CheckGLError();
        

        /*
         * Set the uniform value. In this case a `glm::vec2()` is used to store the x-/y-offset
         * values in the uniform.
         *
         * Original tutorial source snippet:
         *
         *      glUniform2f(offsetLocation, xOffset, yOffset);
         *
         * Note that two slightly different "plain OpenGL versions" alternatives are provided bellow.
         * The first alternative can easily be substituted with the glow-version provided, the second
         * alternativ requires two more changes at other places in this tutorial, namely, a change in
         * method "initializProgram()" and the activation of member "offsetLocation".
         */
        theProgram->setUniform(offsetUniform->name(), glm::vec2(xOffset, yOffset));
//        glUniform2f(theProgram->getUniformLocation(offsetUniform->name(), xOffset, yOffset);
//        CheckGLError();
//        glUniform2f(offsetLocation, xOffset, yOffset);
//        CheckGLError();
        
        
        /*
         * (Re-)Bind the vertexPositionsBuffer object.
         *
         * Orginal tutorial source snippet:
         *
         *      glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
         */
        positionBufferObject->bind();
//        glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer->id());
//        CheckGLError();
        
        /*
         * This encapsulates the OpenGL call:
         *
         *      glEnableVertexAttribArray (0);
         */
        vao->enable(0);
//        glEnableVertexAttribArray(0);
//        CheckGLError();
        
        
        /*
         * The following three lines prepare the rendering of the triangle. The OpenGL function
         * call that ist equivalent to these three lines is the glVertexAttribPointer(...).
         * 
         * Original tutorial source snippet:
         *
         *      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
         *
         * Note, this is one of the few parts in the glow version of the original tutorial where
         * glow does not support a 1:1 mapping of the OpenGL functions and seems to be a bit more
         * "cumbersome" then using plain OpenGL. However, the glow version is easier to read as
         * glow groups setting the parameters in a more meaningfull manner.
         */
        vao->binding(0)->setAttribute(0);
        vao->binding(0)->setFormat(4, GL_FLOAT);
        vao->binding(0)->setBuffer(positionBufferObject, 0, 0);
//        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//        CheckGLError();
        

        /**
         * The following method call encapsulates the plain OpenGL function call glDrawArrays.
         *
         * Original tutorial source snippet:
         *  
         *      glDrawArrays(GL_TRIANGLES, 0, 3);
         */
        vao->drawArrays(GL_TRIANGLES, 0, 3);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        CheckGLError();
        
        /*
         * Encapsulates the plain OpenGL function call glDisableVertexAttribArray ()
         *
         * Original tutorial source snippet:
         *
         *      glDisableVertexAttribArray(0);
         */
        vao->disable(0);
//        glDisableVertexAttribArray(0);
//        CheckGLError();
        
        
        /*
         * Some cleanup work, (1) unbind the vertexPositionsBuffer, (2) release
         * the shader program used for rendering.
         */
        positionBufferObject->unbind();
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        CheckGLError();
        
        theProgram->release();
//        glUseProgram(0);
//        CheckGLError();
        
    }
    
    virtual void idle(glowwindow::Window & window) override {
        window.repaint();
    }
// [END] :: public

    
    
    
// [BEGIN] :: protected
protected:
    /**
     * Initializes the program by compiling the vertex shader and fragment shader, and link them (in)to the program
     * object.
     *
     * This method corresponds to function `VertPositionOffset.cpp::InitializeProgram()` in the original tutorial.
     *
     * The original function source code is as follows:
     *
     *      void InitializeProgram() {
     *
     *              std::vector<GLuint> shaderList;
     *
     *              shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexShader));
     *              shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));
     *
     *              theProgram = CreateProgram(shaderList);
     *
     *              std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
     *
     *              offsetLocation = glGetUniformLocation(theProgram, "offset");
     *      }
     *
     * Note that the creation of the shaders and the program by calling function "CrateShader(...)"
     * and "CreateProgram(...)", as it was done in the tutorial, is completely encapsulated in the
     * glow library. Thus, there is no equivalent implementation for functions CreateProgram(...)
     * and CreateShader(...) in this adapted example!
     */
    void initializeProgram () {
        
        theProgram = new glow::Program();
		theProgram->attach(
                           glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/arcsynthesis/chapter3/vert-position-offset.vert"),
                           glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/arcsynthesis/chapter3/vert-position-offset.frag")
                        );

        /*
         * Explicitly link the program and thereby also compile all the shaders attached to the program.
         * In general, glow will automatically link the program before it is `use()`d, however, to be a
         * little more "verbose" linking is explicitly done here. Further, it is necessary to explicitly
         * link the program here as a plain call to `glGetUniformLocation(...)` will not work otherwise.
         */
        theProgram->link();
        
        /*
         * Create the uniform that will be used to maintain the x-/y-offset in the vertex shader.
         * An alternative to implicitly create the glow::Uniform object is to explicitly create the
         * uniform and add it to the program as follows:
         *
         *        offsetUniform = new glow::Uniform<glm::vec2>("offset");
         *        theProgram->addUniform(offsetUniform);
         *
         */
        offsetUniform = theProgram->getUniform<glm::vec2>("offset");
//        offsetLocation = glGetUniformLocation(theProgram->id(), "offset");
//        CheckGLError();
        
    }
    
    /**
     * This method corresponds to function `cpuPositionsOffset.cpp::InitializeVertexBuffer()`.
     *
     * The original function source code is as follows:
     *
     *      void InitializeVertexBuffer() {
     *
     *          glGenBuffers(1, &positionBufferObject);
     *
     *          glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
     *          glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
     *          glBindBuffer(GL_ARRAY_BUFFER, 0);
     *      }
     *
     * Note that `GL_STREAM_DRAW` is used instead of `GL_STATIC_DRAW` in this tutorial.
     */
    void initializeVertexBuffer () {
        /*
         * Initialize the glow::Buffer as a buffer of type GL_ARRAY_BUFFER. Note, the constructor of
         * glow::Buffer() encapsulates the call to glGenBuffers() and maintains/encapsulates its ID
         * as a member.
         *
         * Original tutorial source snippet:
         *
         *      glGenBuffers(1, &positionBufferObject);
         */
		positionBufferObject = new glow::Buffer(GL_ARRAY_BUFFER);
        
        /*
         * Bind the new glow::Buffer. This call replaces the call to the OpenGL function glBindBuffer(...)
         * as it is used in the original tutorial in function "InitializeVertexBuffer()". Again, glow
         * encapsulates the function call of glBindBuffer(...) in the call of method bind() of the buffer
         * object.
         *
         * Original tutorial source snippet:
         *
         *      glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
         */
        positionBufferObject->bind();
        
        /**
         * Allocate the memory for the vertex positions data and copy the vertex positions array to the
         * allocated buffer. This call replaces the glBufferData(...) call as it is done in the original
         * tutorial source code in function InitializeVertexBuffer().
         *
         * Original tutorial source snippet:
         *
         * glBufferData(
         *              GL_ARRAY_BUFFER,
         *              sizeof(vertexPositions),
         *              vertexPositions,
         *              GL_STREAM_DRAW
         *              );
         *
         * The constant GL_ARRAY_BUFFER is omitted as the vertexPositionsBuffer object encapsulates this
         * constant.
         * 
         * Note the use of `GL_STREAM_DRAW` instead of `GL_STATIC_DRAW` as it was used in previous tutorials.
         */
        positionBufferObject->setData(sizeof(vertexPositions), &vertexPositions, GL_STREAM_DRAW);
        
        /*
         * Unbind the vertexPositionsBuffer as it is done in the tutorial.
         *
         * Original tutorial source snippet:
         *
         * glBindBuffer(GL_ARRAY_BUFFER, 0);
         */
        positionBufferObject->unbind();
    }
    
    /**
     * Computes the x-/y-offset of the triangle depending on the elapsed time.
     *
     * This method computes the x-/y-offset to move the rendered geometry on a circular path around the
     * center of the current viewport so that it will be at its initial position every `fLoopDuration`
     * seconds.
     *
     * This method also demonstrates the use of the `glowutils::Timer` class that replaces the use of
     * `glutGet(GLUT_ELAPSED_TIME)` as used in the original tutorial source code.
     *
     * This method corresonds to function `ComputePositionOffset()` in the original tutorial source code
     * of file `cpuPositionOffset.cpp`. The original source code of function `ComputePositionOFfset()` is
     * as follows:
     *
     *     void ComputePositionOffsets(float &fXOffset, float &fYOffset)
     *     {
     *          const float fLoopDuration = 5.0f;
     *          const float fScale = 3.14159f * 2.0f / fLoopDuration;
     *
     *          float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
     *
     *          float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
     *
     *          fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
     *          fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
     *     }
     *
     * @param fXOffset Reference to a `float` to store the _x-offset_ for the next rendering pass.
     * @param fYOffset Reference to a `float` to store the _y-offset_ for the next rendering pass.
     */
    void computePositionOffset (float& fXOffset, float& fYOffset) {
        
        const float fLoopDuration = 5.0f;
        const float fScale = 3.14159f * 2.0f / fLoopDuration;
        
        /*
         * The glowutils::Timer returns the timer->elapsed() time in nanoseconds. This is a pretty
         * simple example of using the glowutils::Timer class and replaces the freeglut function
         * calls.
         * 
         * Original tutorial source code snipet:
         *
         *      float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
         *
         * Note that the division is done by 1,000,000,000.0f instead of 1000.0f as (per default)
         * the `glowutils::Timer` has a higher resolution as the corresponding freeglut function.
         */
        float fElapsedTime {static_cast<float>(timer->elapsed() / 1000000000.0f)};

        float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
        
        fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
        fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
    }
    
// [END] :: protected

    
    

// [BEGIN] :: private
private:
    
    /**
     * The glow::VertexArrayObject that replaces the GLuint field with the same name in the original tutorial.
     */
	glow::VertexArrayObject* vao;
//    GLuint vao;
    
    /**
     * The glow::Buffer object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial member declaration is:
     * 
     *      GLuint positionBufferObject;
     */
	glow::Buffer* positionBufferObject;
//    GLuint positionBufferObject; 
    
    /**
     * The `glow::Uniform` of type `glm::vec2` that is used to maintain the x-/y-offset to be applied to the
     * geometry in the vertex shader.
     *
     * Original tutorial member declaration is:
     *
     *      GLuint offsetLocation;
     *
     * Note that the name of the `glow::Uniform` member differs from the name of the original tutorial (that
     * is _offsetLocation_). This is different to the names of the other members and this difference in the
     * naming is _on purpose_ to highlight that the member is not only a location index but an offset uniform
     * object (all other members do not imply such a constraint, therefore, they names where retained).
     */
    glow::Uniform<glm::vec2>* offsetUniform;
//    GLuint offsetLocation;
    
    /**
     * The glow::Program object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial member declaration is:
     *
     *      GLuint theProgram;
     */
	glow::Program* theProgram;
//    GLuint theProgram;
    
    /**
     * A glowutils::Timer to keep track of the elapsed time and update triangle positions accordingly.
     */
    glowutils::Timer* timer;
    
// [END] :: private
    
}; // [END] class EventHandler



/**
 * This example implements the first tutorial of "Learning Modern 3D Graphics Programming" by
 * Jason L. McKesson (cf. http://arcsynthesis.org/gltut/index.html) using glow instead of freeglut.
 */
int main(int /*argc*/, char* /*argv*/[]) {
    
    glowwindow::ContextFormat format;
    format.setVersion(3, 0);
    
    glowwindow::Window window;
    window.setEventHandler(new EventHandler());
    
    if (window.create(format, "Learning Modern 3D Graphics Programming [with glow] -- Moving Triangle [Vertex Position Offset]")) {
        
        window.context()->setSwapInterval(glowwindow::Context::VerticalSyncronization);
        window.show();
        window.resize(500, 500);
        
        return glowwindow::MainLoop::run();
        
    } else {
        
        return 1;
        
    }
}
