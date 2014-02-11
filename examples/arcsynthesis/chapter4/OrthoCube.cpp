

#include <string>

// [BEGIN] Includes of GLOW
#include <glow/debugmessageoutput.h>
#include <glow/State.h>
#include <glow/Buffer.h>
#include <glow/Error.h>
#include <glow/Program.h>
#include <glow/Shader.h>
#include <glow/String.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
// [END] Includes of GLOW

// [BEGIN] Includes of GLOWUTILS
#include <glowutils/global.h>
#include <glowutils/StringTemplate.h>
// [END] Includes of GLOWUTILS

// [BEGIN] Includes of GLOWWINDOW
#include <glowwindow/Context.h>
#include <glowwindow/events.h>
#include <glowwindow/WindowEventHandler.h>
#include <glowwindow/Window.h>
// [END] Includes of GLOWWINDOW





/**
 * Ananonymous namespace in which the vertex and fragment shader source code is declared and initialized
 * as well as the float array that maintains the raw vertex positions of the triangle to draw.
 */
namespace {
    /**
     * The float array that maintains the geometry and color information of the scene to render.
     */
    const float vertexData[] {
        
        /*
         * Vertex positions of the rectangular prism (cuboid) to render.
         */
        
        //1st triangle of the front-facing cuboid surface.
        0.25f,  0.25f, 0.75f, 1.0f,
        0.25f, -0.25f, 0.75f, 1.0f,
        -0.25f,  0.25f, 0.75f, 1.0f,
        
        //2nd triangle of the front-facing cuboid surface.
        0.25f, -0.25f, 0.75f, 1.0f,
        -0.25f, -0.25f, 0.75f, 1.0f,
        -0.25f,  0.25f, 0.75f, 1.0f,
        
        //1st triangle of the back-facing cuboid surface.
        0.25f,  0.25f, -0.75f, 1.0f,
        -0.25f,  0.25f, -0.75f, 1.0f,
        0.25f, -0.25f, -0.75f, 1.0f,
        
        //2nd triangle of the back-facing cuboid surface.
        0.25f, -0.25f, -0.75f, 1.0f,
        -0.25f,  0.25f, -0.75f, 1.0f,
        -0.25f, -0.25f, -0.75f, 1.0f,
        
        //1st triangle of the left-facing cuboid surface.
        -0.25f,  0.25f,  0.75f, 1.0f,
        -0.25f, -0.25f,  0.75f, 1.0f,
        -0.25f, -0.25f, -0.75f, 1.0f,
        
        //2nd triangle of the left-facing cuboid surface.
        -0.25f,  0.25f,  0.75f, 1.0f,
        -0.25f, -0.25f, -0.75f, 1.0f,
        -0.25f,  0.25f, -0.75f, 1.0f,
        
        //1st triangle of the right-facing cuboid surface.
        0.25f,  0.25f,  0.75f, 1.0f,
        0.25f, -0.25f, -0.75f, 1.0f,
        0.25f, -0.25f,  0.75f, 1.0f,
        
        //2nd triangle of the right-facing cuboid surface.
        0.25f,  0.25f,  0.75f, 1.0f,
        0.25f,  0.25f, -0.75f, 1.0f,
        0.25f, -0.25f, -0.75f, 1.0f,
        
        //1st triangle of the top-facing cuboid surface.
        0.25f,  0.25f, -0.75f, 1.0f,
        0.25f,  0.25f,  0.75f, 1.0f,
        -0.25f,  0.25f,  0.75f, 1.0f,
        
        //2nd triangle of the top-facing cuboid surface.
        0.25f,  0.25f, -0.75f, 1.0f,
        -0.25f,  0.25f,  0.75f, 1.0f,
        -0.25f,  0.25f, -0.75f, 1.0f,
        
        //1st triangle of the bottom-facing cuboid surface.
        0.25f, -0.25f, -0.75f, 1.0f,
        -0.25f, -0.25f,  0.75f, 1.0f,
        0.25f, -0.25f,  0.75f, 1.0f,
        
        //2nd triangle of the bottom-facing cuboid surface.
        0.25f, -0.25f, -0.75f, 1.0f,
        -0.25f, -0.25f, -0.75f, 1.0f,
        -0.25f, -0.25f,  0.75f, 1.0f,
        
        
        /*
         * Vertex colors of the cuboid.
         */
        // Color of the 1st triangle of the front-facing cuboid surface.
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        
        // Color of the 2nd triangle of the front-facing cuboid surface.
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        
        // Color of the 1st triangle of the back-facing cuboid surface.
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        
        // Color of the 2nd triangle of the back-facing cuboid surface.
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        
        // Color of the 1st triangle of the left-facing cuboid surface.
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        
        // Color of the 2nd triangle of the left-facing cuboid surface.
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        
        // Color of the 1st triangle of the right-facing cuboid surface.
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        
        // Color of the 2nd triangle of the right-facing cuboid surface.
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        
        // Color of the 1st triangle of the top-facing cuboid surface.
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        
        // Color of the 2nd triangle of the top-facing cuboid surface.
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        
        // Color of the 1st triangle of the bottom-facing cuboid surface.
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        
        // Color of the 1st triangle of the bottom-facing cuboid surface.
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
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
        
        // cf. protected methods for implementation of "initializeProgram()" and "initializeVertexBuffer()"
        initializeProgram();
        initializeVertexBuffer();
        
        /*
         * Create the vertex array object and bind it
         *
         * Original tutorial source snippet:
         *
         *      	glGenBuffers(1, &positionBufferObject);
         *          glBindVertexArray(vao);
         */
		vao = new glow::VertexArrayObject();
        vao->bind();
        
        /*
         * Enable face culling.
         *
         * Original tutorial source snippet:
         *
         *      	glEnable(GL_CULL_FACE);
         */
        glow::State state;
        state.enable(GL_CULL_FACE);
        state.cullFace(GL_BACK);
//        state.frontFace(GL_CCW);
        glFrontFace(GL_CW);

        
//        glow::enable(GL_CULL_FACE);
//        glEnable(GL_CULL_FACE);
//        CheckGLError();
        
//        glCullFace(GL_BACK);
//        glFrontFace(GL_CW);

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
     * This method corresponds to tut1.cpp::display() and is called whenever
     * a "PaintEvent" is triggered. The original function source code is as
     * follows:
     *
     *      void display() {
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
     *      }
     *
     * Note, the function call "glutSwapBuffers()" is a call of a freeglut function. As this tutorial
     * does not use freeglut this function call is not to be found in this method!
     */
    virtual void paintEvent(glowwindow::PaintEvent &) override {
        
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
         * Note, when using the plain OpenGL function use `theProgram->id()` to retrieve the
         * `GLuint` required to identify the program object. Further, using glow, a program
         * must be linked once before (`theProgram->link()`) it is used.
         */
		theProgram->use();
//        glUseProgram(theProgram->id());
//        CheckGLError();
        

        /*
         * Set the offset uniform value.
         *
         * Original tutorial source snippet:
         * 
         *      glUniform2f(offsetUniform, 0.5f, 0.25f);
         */
        theProgram->setUniform(offsetUniform->name(), glm::vec2 {0.5f, 0.25f});
//        glUniform2f(theProgram->getUniformLocation(offsetUniform->name()), 0.5f, 0.25f);
//        CheckGLError();
        
        
        /*
         * (Re-)Bind the vertexPositionsBuffer object.
         *
         * Orginal tutorial source snippet:
         *
         *      glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
         */
        vertexBufferObject->bind();
//        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject->id());
//        CheckGLError();
        
        /*
         * This encapsulates the OpenGL call:
         *
         *      glEnableVertexAttribArray (0);
         *      glEnableVertexAttribArray (1);
         */
        vao->enable(0);
        vao->enable(1);
//        glEnableVertexAttribArray(0);
//        CheckGLError();
//        glEnableVertexAttribArray(1);
//        CheckGLError();
        
        
        /*
         * The following three lines prepare the rendering of the triangle. The OpenGL function
         * call that ist equivalent to these three lines is the glVertexAttribPointer(...).
         * 
         * Original tutorial source snippet:
         *
         *      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
         *      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);
         */
        vao->binding(0)->setAttribute(0);
        vao->binding(0)->setFormat(4, GL_FLOAT);
        vao->binding(0)->setBuffer(vertexBufferObject, 0, 0);
//        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//        CheckGLError();
        vao->binding(1)->setAttribute(1);
        vao->binding(1)->setFormat(4, GL_FLOAT);
        vao->binding(1)->setBuffer(vertexBufferObject, sizeof(vertexData)/2, 0);
//        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertexData)/2));
//        CheckGLError();
        
        /*
         * The following method call encapsulates the plain OpenGL function call glDrawArrays.
         *
         * Original tutorial source snippet:
         *  
         *      glDrawArrays(GL_TRIANGLES, 0, 36);
         */
        vao->drawArrays(GL_TRIANGLES, 0, 36);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        CheckGLError();
        
        /*
         * Encapsulates the plain OpenGL function call glDisableVertexAttribArray ()
         *
         * Original tutorial source snippet:
         *
         *      glDisableVertexAttribArray(0);
         */
        vao->disable(0);
        vao->disable(1);
//        glDisableVertexAttribArray(0);
//        glDisableVertexAttribArray(1);
//        CheckGLError();
        
        
        /*
         * Some cleanup work, (1) unbind the vertexPositionsBuffer, (2) release
         * the shader program used for rendering.
         */
        vertexBufferObject->unbind();
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
     * This method corresponds to function OrthoCube.cpp::InitializeProgram(). The original function
     * source code is as follows:
     *
     *      void InitializeProgram() {
     *
     *              std::vector<GLuint> shaderList;
     *
     *              shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "OrthoWithOffset.vert"));
     *              shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "StandardColors.frag"));
     *
     *              theProgram = CreateProgram(shaderList);
     *
     *              offsetUniform = glGetUniformLocation(theProgram, "offset");
     *
     *      }
     */
    void initializeProgram () {
        
        theProgram = new glow::Program();
		theProgram->attach(
                           glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/arcsynthesis/chapter4/ortho-cube.vert"),
                           glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/arcsynthesis/chapter4/ortho-cube.frag")
                        );
        
//        theProgram->link();
        // create the offset uniform
        offsetUniform = theProgram->getUniform<glm::vec2>("offset");
    }
    
    /**
     * This method corresponds to function tut1.cpp::InitializeVertexBuffer(). The original function
     * source code is as follows:
     *
     *      void InitializeVertexBuffer() {
     *
     *          glGenBuffers(1, &positionBufferObject);
     *
     *          glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
     *          glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
     *          glBindBuffer(GL_ARRAY_BUFFER, 0);
     *      }
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
		vertexBufferObject = new glow::Buffer(GL_ARRAY_BUFFER);
        
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
        vertexBufferObject->bind();
        
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
         *              GL_STATIC_DRAW
         *              );
         *
         * The constant GL_ARRAY_BUFFER is omitted as the vertexPositionsBuffer object encapsulates this
         * constant. Further, the constant GL_STATIC_DRAW could be omitted too as that parameter's default
         * value is already GL_STATIC_DRAW, however, we decided to explicitly state it here to stay as
         * close as possible to the original tutorial's code.
         */
        vertexBufferObject->setData(sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
        
        /*
         * Unbind the vertexPositionsBuffer as it is done in the tutorial.
         *
         * Original tutorial source snippet:
         *
         * glBindBuffer(GL_ARRAY_BUFFER, 0);
         */
        vertexBufferObject->unbind();
    }
// [END] :: protected

    
    

// [BEGIN] :: private
private:
    
    /**
     * The glow::VertexArrayObject that replaces the GLuint field with the same name in the original tutorial.
     */
	glow::VertexArrayObject* vao;
    
    /**
     * The glow::Buffer object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial field declaration is:
     * 
     *      GLuint positionBufferObject;
     */
	glow::Buffer* vertexBufferObject;
    
    /**
     * The glow::Program object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial field declaration is:
     *
     *      GLuint theProgram;
     */
	glow::Program* theProgram;
    
    /**
     * The uniform that maintains the offset vector to be applied to the vertices of the geometry.
     */
    glow::Uniform<glm::vec2>* offsetUniform;
    
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
    
    if (window.create(format, "Learning Modern 3D Graphics Programming [with glow] -- Ortho Cube!")) {
        
        window.context()->setSwapInterval(glowwindow::Context::VerticalSyncronization);
        window.show();
        window.resize(500, 500);
        
        return glowwindow::MainLoop::run();
        
    } else {
        
        return 1;
        
    }
}
