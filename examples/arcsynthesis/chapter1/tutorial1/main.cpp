
#include <glow/Buffer.h>
#include <glow/Error.h>
#include <glow/debugmessageoutput.h>
#include <glow/Program.h>
#include <glow/Shader.h>
#include <glow/String.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>

#include <glowutils/StringTemplate.h>

#include <glowwindow/Context.h>
#include <glowwindow/WindowEventHandler.h>
#include <glowwindow/Window.h>



namespace {
    /**
     * This is the source of the vertex shader as a "raw string".
     */
    const char* vertexShaderCode = R"(
#version 330
    
layout(location = 0) in vec4 position;
    
void main() {
    gl_Position = position;
}
    )";

    
    
    /**
     * This is the source of the vertex shader as a "raw string".
     */
    const char* fragmentShaderCode = R"(
#version 330
    
out vec4 outputColor;
    
void main() {
    outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
    )";

    
    
    /*
     * The raw vertex positions of the triangle to draw, stored in a
     * glow::Array instead of a simple float array as it is done in
     * the original tutorial.
     *
     * original source snippet:
     *
     * const float vertexPositions[] {
     *    0.75f, 0.75f, 0.0f, 1.0f,
     *    0.75f, -0.75f, 0.0f, 1.0f,
     *    -0.75f, -0.75f, 0.0f, 1.0f,
     * };
     */
    const glow::Array<glm::vec4> vertexPositions({
        glm::vec4(0.75, 0.75, 0.0, 1.0),
        glm::vec4(0.75, -0.75, 0.0, 1.0),
        glm::vec4(-0.75, -0.75, 0.0, 1.0)
    });
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
     * This method corresponds to function tut1.cpp::init() -- that in turn calls function
     * InitializePorgram() and InitializeVertexBuffer() -- in the original source code of
     * the tutorial.
     */
    virtual void initialize(glowwindow::Window &) override {
        
        glow::debugmessageoutput::enable();
        
        // cf. protected-block for implementation of methdos "initializeProgram()" and "initializeVertexBuffer()"
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
    virtual void framebufferResizeEvent(glowwindow::ResizeEvent & event) override {
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
     */
    virtual void paintEvent(glowwindow::PaintEvent &) override {
        
        // set color to clear the screen, check for an OpenGL error, actually
        // clear the screen and check for an OpenGL error again.
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        CheckGLError();
        glClear(GL_COLOR_BUFFER_BIT);
        CheckGLError();

        
		program->use();
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer->id());
        
        /*
         * This encapsulates the OpenGL call:
         *
         *      glEnableVertexAttribArray (0);
         */
        vao->enable(0);
//        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*
         * This encapsulates the OpenGL call:
         *
         *      glDisableVertexAttribArray (0);
         */
        vao->disable(0);
//        glDisableVertexAttribArray(0);

        
        
//        vao->binding(0)->setAttribute(0);
//        vao->binding(0)->setBuffer(vertexPositionsBuffer, 0, sizeof(glm::vec4));
//        vao->binding(0)->setFormat(4, GL_FLOAT);
//        vao->enable(0);
//        vao->drawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        program->release();
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
     * and "CreateProgram(...)", as it was done in the tutorial, is now the creation of two glow::Shader
     * objects and a glow::Program object, respectively.
     */
    void initializeProgram () {

        glowutils::StringTemplate* vertexShaderSource = new glowutils::StringTemplate(new glow::String(vertexShaderCode));
        glowutils::StringTemplate* fragmentShaderSource = new glowutils::StringTemplate(new glow::String(fragmentShaderCode));
        
        program = new glow::Program();
		program->attach(
                        new glow::Shader(GL_VERTEX_SHADER, vertexShaderSource),
                        new glow::Shader(GL_FRAGMENT_SHADER, fragmentShaderSource)
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
         * Initialize the glow::Buffer as a buffer of type GL_ARRAY_BUFFER.
         * Note: The call to glGenBuffers(1, &positionBufferObject) -- the
         * creation of a (single) new buffer is done during initialization
         * of the glow::Buffer!
         *
         * original source snippet:
         *
         * glGenBuffers(1, &positionBufferObject);
         */
		vertexPositionsBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
        
        /*
         * Bind the new glow::Buffer. This call replaces the call to the OpenGL
         * function glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject) as it is
         * done in the tutorial in function "InitializeVertexBuffer()".
         *
         * original source snippet:
         *
         * glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
         */
        vertexPositionsBuffer->bind();
        
        /**
         * Copy the vertex positions into the vertexPositionsBuffer object. This
         * call replaces the glBufferData(...) call as it is done in the original
         * tutorial source code in function "InitializeVertexBuffer()".
         *
         * original source snippet:
         *
         * glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
         */
        vertexPositionsBuffer->setData(vertexPositions);
        
        /*
         * Unbind the vertexPositionsBuffer as it is done in the tutorial.
         *
         * original source snippet:
         *
         * glBindBuffer(GL_ARRAY_BUFFER, 0);
         */
        vertexPositionsBuffer->unbind();
    }
// [END] :: protected

    
    

// [BEGIN] :: private
private:
	glow::VertexArrayObject* vao;
	glow::Buffer* vertexPositionsBuffer;
	glow::Program* program;
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
//        window.context()->setSwapInterval(glowwindow::Context::VerticalSyncronization);
        window.show();
        window.resize(640, 640);
        
        return glowwindow::MainLoop::run();
    } else {
        return 1;
    }
}
