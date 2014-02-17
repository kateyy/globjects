

#include <string>
#include <iostream>

// [BEGIN] Includes of GLOW
#include <glow/Buffer.h>
#include <glow/Error.h>
#include <glow/debugmessageoutput.h>
#include <glow/Program.h>
#include <glow/Shader.h>
#include <glow/String.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
// [END] Includes of GLOW

// [BEGIN] Includes of GLOWUTILS
#include <glowutils/global.h>
// [END] Includes of GLOWUTILS

// [BEGIN] Includes of GLOWWINDOW
#include <glowwindow/Context.h>
#include <glowwindow/events.h>
#include <glowwindow/WindowEventHandler.h>
#include <glowwindow/Window.h>
// [END] Includes of GLOWWINDOW





/**
 * Ananonymous namespace used to declare and initialize the raw vertex positions/
 * colors of the triangle to draw.
 */
namespace {
    /**
     * The vertex positions/data (vertex positions followed by vertex colors) of
     * the triangle to draw (in clip-space).
     */
    const float vertexData[] {
        //position of vertex 1 (upper)
        0.0f, 0.5f, 0.0f, 1.0f,
        //position of vertex 2 (lower-right)
        0.5f, -0.366f, 0.0f, 1.0f,
        //position of vertex 3 (lower-left)
        -0.5f, -0.366f, 0.0f, 1.0f,
        //color (red) of vertex 1 (upper)
        1.0f, 0.0f, 0.0f, 1.0f,
        //color (green) of vertex 2 (lower-right)
        0.0f, 1.0f, 0.0f, 1.0f,
        //color (blue) of vertex 3 (lower-left)
        0.0f, 0.0f, 1.0f, 1.0f
    };
    
    /**
     * The enum that maintains the possible viewport positions.
     */
    enum Viewport {
        DEFAULT,
        UPPER_HALF,
        LOWER_HALF
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
     * Initializes the shader program and the vertex buffer that stores the data of the geometry to
     * be rendered.
     *
     * This method corresponds to function FragPosition.cpp::init() -- that in turn calls function
     * InitializePorgram() and InitializeVertexBuffer() -- in the original source code of the tutorial.
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
         * As member theProgram is a glow::Program object theProgram-id() must be used to obtain
         * the GLuint that identifies the program.
         */
		theProgram->use();
//        glUseProgram(theProgram->id());
//        CheckGLError();
        
        
        
        /*
         * (Re-)Bind the vertexPositionsBuffer object.
         *
         * Orginal tutorial source snippet:
         *
         *      glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
         */
        vertexBufferObject->bind();
//        glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer->id());
//        CheckGLError();

        
        
        /*
         * Enable the two vertex attributes (position and color of the vertices) used for rendering.
         * This encapsulates the OpenGL calls:
         *
         *      glEnableVertexAttribArray (0);
         *      glEnableVertexAttribArray (1);
         *
         * Note that the values passed to enable/glEnableVertexAttribArray are the attribute indices
         * used in the vertex shader (layout(location=0) and layout(location=1), cf. vertex-colors.vert).
         */
        vao->enable(0);
        vao->enable(1);
//        glEnableVertexAttribArray(0);
//        CheckGLError();
//        glEnableVertexAttribArray(1);
//        CheckGLError();

        
        /*
         * The following six lines prepare the rendering of the triangle. The OpenGL function
         * call that ist equivalent to these three lines is the glVertexAttribPointer(...).
         *
         * Original tutorial source snippet (only two lines!):
         *
         *      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
         *      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);
         *
         * Note that glow is a little more "verbose" as using the plain OpenGL functions as it is
         * done in the original tutorial.
         */
        vao->binding(0)->setAttribute(0);
        vao->binding(0)->setFormat(4, GL_FLOAT);
        vao->binding(0)->setBuffer(vertexBufferObject, 0, 0);
        //        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        //        CheckGLError();
        vao->binding(0)->setAttribute(1);
        vao->binding(0)->setFormat(4, GL_FLOAT);
        vao->binding(0)->setBuffer(vertexBufferObject, 48, 0);
//        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);
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
         * Disable the two vertex attributes in use. This encapsulates the plain OpenGL function
         * call glDisableVertexAttribArray() for both of the attributes in use.
         *
         * Original tutorial source snippet:
         *
         *      glDisableVertexAttribArray(0);
         *      glDisableVertexAttribArray(1);
         */
        vao->disable(0);
//        glDisableVertexAttribArray(0);
//        CheckGLError();
        vao->disable(1);
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
    
    /**
     * Handles keyboard events to change the viewport as suggested in the "Further Studies" section of
     * the original FragPosition tutorial (chapter 1, tutorial 2.1).
     */
    virtual void keyPressEvent(glowwindow::KeyEvent & event) override
    {
        switch (event.key())
        {
            case GLFW_KEY_C: {
                
                /*
                 * Maintain the new viewport position and dimension in a glm vec of four int values.
                 * Note that the framebufferSize is used to comput the new viewport NOT the window
                 * size. While using the window size (e.g. event.window()->width()) would work on a
                 * non-retina/-high-resolution display, using the window size on a retina display will
                 * not work properly. Thererfore, it is best to use the framebufferSize to compute the
                 * viewport position/dimension.
                 */
                glm::ivec4 vpv {0,0,event.window()->framebufferSize()};
                
                // Check the viewport flag.
                if (activeViewport == Viewport::DEFAULT) {
                    
                    activeViewport = Viewport::UPPER_HALF;
                    /*
                     * Resizes the viewport so that the viewport only occupies the upper half of the
                     * space provided by the window.
                     */
                    glViewport(vpv.x, vpv.y, vpv.z, vpv.w);
                    CheckGLError();
                    
                } else if (activeViewport == Viewport::UPPER_HALF) {
                    
                    activeViewport = Viewport::LOWER_HALF;
                    /*
                     * Resizes the viewport so that the viewport only occupies the lower half of the
                     * space provided by the window.
                     */
                    glViewport(vpv.x, vpv.w/2, vpv.z, vpv.w/2);
                    CheckGLError();
                    
                } else if (activeViewport == Viewport::LOWER_HALF) {
                    
                    activeViewport = Viewport::DEFAULT;
                    /*
                     * Resizes the viewport so that the viewport occupies the whole space provided by
                     * the window.
                     */
                    glViewport(vpv.x, vpv.y, vpv.z, vpv.w/2);
                    CheckGLError();
                    
                } else {
                    std::cout << "UNDEFINED VIEWPORT POSITION! Setting to Viewport::DEFAULT" << std::endl;
                    activeViewport = Viewport::DEFAULT;
                    /*
                     * Resizes the viewport so that the viewport occupies the whole space provided by
                     * the window.
                     */
                    glViewport(vpv.x, vpv.y, vpv.z, vpv.w);
                    CheckGLError();
                }
                
                break;
            }
                
            default: {
                
                std::cout << "Please use the \'c\' key to iterate between possible viewport positions" << std::endl;
                break;
            }
        }
        
    }
    // [END] :: public
    
    
    
    
    // [BEGIN] :: protected
protected:
    /**
     * This method corresponds to function VertexPositions.cpp::InitializeProgram().
     * The original function source code is as follows:
     *
     *      void InitializeProgram() {
     *
     *          std::vector<GLuint> shaderList;
     *
     *          shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "VertexColors.vert"));
     *          shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "VertexColors.frag"));
     *
     *          theProgram = Framework::CreateProgram(shaderList);
     *      }
     *
     * Note that the creation of the shaders and the program by calling function "Framework::LoadShader(...)"
     * and "Framework::CreateProgram(...)", as it is done in the tutorial, is completely encapsulated in the
     * glow library. Likewise, the glow library supports creating shaders from source files which is shown here
     * using function glowutils::createShaderFromFile(...).
     */
    void initializeProgram () {
        
        theProgram = new glow::Program();
		theProgram->attach(
                           glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/arcsynthesis/chapter2/vertex-colors-further-studies.vert"),
                           glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/arcsynthesis/chapter2/vertex-colors-further-studies.frag")
                           );
    }
    
    /**
     * This method corresponds to function VertexPositions.cpp::InitializeVertexBuffer().
     * The original function source code is as follows:
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
     * The active viewport(-position) to use.
     */
    Viewport activeViewport {DEFAULT};
    
    /**
     * The glow::VertexArrayObject that replaces the GLuint field with the same name in the original tutorial.
     */
	glow::VertexArrayObject* vao;
//    GLuint vao;
    
    /**
     * The glow::Buffer object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial field declaration is:
     *
     *      GLuint vertexBufferObject;
     */
	glow::Buffer* vertexBufferObject;
//    GLuint vertexBufferObject;
    
    /**
     * The glow::Program object that replaces the GLuint field with the same name in the original tutorial.
     *
     * Original tutorial field declaration is:
     *
     *      GLuint theProgram;
     */
	glow::Program* theProgram;
//    GLuint theProgram;
    
// [END] :: private
    
}; // [END] class EventHandler



/**
 * This example implements the first tutorial of "Learning Modern 3D Graphics Programming" by
 * Jason L. McKesson (cf. http://arcsynthesis.org/gltut/index.html) using glow instead of freeglut.
 *
 * The "Further Studies" extension of tutorial 2.2 in the first chapter of the tutorial referenced
 * above. This tutorial extends the VertexColors tutorial by combining the vertex shader of the
 * vertex colors tutorial and the fragment shader of the FragPosition tutorial so that the colors
 * passed from the vertex shader will further be processed in the fragment shader (cf. vertex-colors-
 * further-studies.frag).
 *
 * IMPORTANT: On computers with retina displays or high resolution displays the result of this
 * tutorial will differ from normal displays and from the result presented in the tutorial! Try
 * to adapt the shader "frag-position.frag" as explained in the shader source codes to get the
 * same result on a high resolution display.
 */
int main(int /*argc*/, char* /*argv*/[]) {
    
    glowwindow::ContextFormat format;
    format.setVersion(3, 0);
    
    glowwindow::Window window;
    window.setEventHandler(new EventHandler());
    
    if (window.create(format, "Learning Modern 3D Graphics Programming [with glow] -- Playing with Colors [VertexColors]")) {
        
        window.context()->setSwapInterval(glowwindow::Context::VerticalSyncronization);
        window.show();
        window.resize(500, 500);
        
        return glowwindow::MainLoop::run();
        
    } else {
        
        return 1;
        
    }
}
