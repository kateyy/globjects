

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
#include <glowutils/StringTemplate.h>
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
     * The source of the vertex shader as a string.
     */
    const std::string vertexShaderSource {
        "#version 330\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main() {\n"
        "\n"
        "gl_Position = position;\n"
        "}\n"
    };
    
    /**
     * The source of the fragment shader as a string.
     */
    const std::string fragmentShaderSource {
        "#version 330\n"
        "\n"
        "out vec4 outputColor;\n"
        "\n"
        "void main() {\n"
        "\n"
        "outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n"
    };

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
     * This method corresponds to function tut1.cpp::InitializeProgram(). The original function
     * source code is as follows:
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
                        glow::Shader::fromString(GL_VERTEX_SHADER, vertexShaderSource),
                        glow::Shader::fromString(GL_FRAGMENT_SHADER, fragmentShaderSource)
                        );
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
         *              GL_STATIC_DRAW
         *              );
         *
         * The constant GL_ARRAY_BUFFER is omitted as the vertexPositionsBuffer object encapsulates this
         * constant. Further, the constant GL_STATIC_DRAW could be omitted too as that parameter's default
         * value is already GL_STATIC_DRAW, however, we decided to explicitly state it here to stay as
         * close as possible to the original tutorial's code.
         */
        positionBufferObject->setData(sizeof(vertexPositions), &vertexPositions, GL_STATIC_DRAW);
        
        /*
         * Unbind the vertexPositionsBuffer as it is done in the tutorial.
         *
         * Original tutorial source snippet:
         *
         * glBindBuffer(GL_ARRAY_BUFFER, 0);
         */
        positionBufferObject->unbind();
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
     * Original tutorial field declaration is:
     * 
     *      GLuint positionBufferObject;
     */
	glow::Buffer* positionBufferObject;
//    GLuint positionBufferObject;
    
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
 */
int main(int /*argc*/, char* /*argv*/[]) {
    
    glowwindow::ContextFormat format;
    format.setVersion(3, 0);
    
    glowwindow::Window window;
    window.setEventHandler(new EventHandler());
    
    if (window.create(format, "Learning Modern 3D Graphics Programming [with glow] -- Hello, Triangle!")) {
        
        window.context()->setSwapInterval(glowwindow::Context::VerticalSyncronization);
        window.show();
        window.resize(500, 500);
        
        return glowwindow::MainLoop::run();
        
    } else {
        
        return 1;
        
    }
}
