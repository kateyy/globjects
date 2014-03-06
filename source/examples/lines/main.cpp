#include <GL/glew.h>

#include <glm/gtc/random.hpp>

#include <algorithm>
#include <random>

#include <glow/Error.h>
#include <glow/logging.h>
#include <glow/Buffer.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/Shader.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/debugmessageoutput.h>

#include <glowutils/ScreenAlignedQuad.h>
#include <glowwindow/ContextFormat.h>
#include <glowwindow/Context.h>
#include <glowwindow/Window.h>
#include <glowwindow/WindowEventHandler.h>
#include <glowwindow/events.h>

#include <ExampleWindowEventHandler.h>

using namespace glowwindow;

const char* vertexShaderSource = R"(
#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout (location=0) in vec2 in_position;
layout (location=1) in vec4 in_color;

out vec4 color;

void main()
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    color = in_color;
}

)";

const char* fragmentShaderSource = R"(
#version 150
#extension GL_ARB_explicit_attrib_location : enable

in vec4 color;

layout (location=0) out vec4 outColor;

void main()
{
    outColor = color;
}

)";

class EventHandler : public ExampleWindowEventHandler
{
public:
    struct Vertex{glm::vec2 pos; glm::vec4 color;};

    EventHandler()
    {
    }

    virtual ~EventHandler()
    {
    }

    virtual void initialize(Window & window) override
    {
        glow::debugmessageoutput::enable();

        glClearColor(1.f, 1.f, 1.f, 1.f);
        CheckGLError();

        m_vao = new glow::VertexArrayObject;
        m_vbo = new glow::Buffer(GL_ARRAY_BUFFER);

        makeVertices();

        m_vao->binding(0)->setAttribute(0);
        m_vao->binding(0)->setBuffer(m_vbo, 0, sizeof(Vertex));
        m_vao->binding(0)->setFormat(2, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));

        m_vao->binding(1)->setAttribute(1);
        m_vao->binding(1)->setBuffer(m_vbo, 0, sizeof(Vertex));
        m_vao->binding(1)->setFormat(4, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));

        m_vao->enable(0);
        m_vao->enable(1);

        m_program = new glow::Program;
        m_program->attach(
            glow::Shader::fromString(GL_VERTEX_SHADER, vertexShaderSource),
            glow::Shader::fromString(GL_FRAGMENT_SHADER, fragmentShaderSource)
        );

        m_colorTexture = new glow::Texture(GL_TEXTURE_2D);

        m_colorTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_colorTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_colorTexture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_colorTexture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        m_colorTexture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        m_depthBuffer = new glow::RenderBufferObject;

        m_fbo = new glow::FrameBufferObject;
        m_fbo->attachTexture(GL_COLOR_ATTACHMENT0, m_colorTexture);
        m_fbo->attachRenderBuffer(GL_DEPTH_ATTACHMENT, m_depthBuffer);

        m_fbo->unbind();

        m_quad = new glowutils::ScreenAlignedQuad(m_colorTexture);

        window.addTimer(0, 0);
    }

    virtual void finalize(Window & ) override
    {
        m_vao = nullptr;
        m_vbo = nullptr;
        m_program = nullptr;
        m_fbo = nullptr;
        m_quad = nullptr;
    }

    virtual void framebufferResizeEvent(ResizeEvent & event) override
    {
        int width = event.width();
        int height = event.height();
    	int side = std::min<int>(width, height);

        glViewport((width - side) / 2, (height - side) / 2, side, side);
        CheckGLError();

        m_colorTexture->image2D(0, GL_RGBA8, glm::ivec2(width, height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        m_depthBuffer->storage(GL_DEPTH_COMPONENT24, width, height);
    }

    virtual void paintEvent(PaintEvent &) override
    {
        m_fbo->bind();
        m_fbo->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_program->use();
        m_vao->drawArrays(GL_LINES, 0, (int)m_vertices.size());
        m_program->release();
        m_fbo->unbind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CheckGLError();
        m_quad->draw();
    }

    virtual void timerEvent(TimerEvent & event) override
    {
        event.window()->repaint();
    }

    virtual void keyPressEvent(KeyEvent & event) override
    {
        if (event.key() == GLFW_KEY_R)
        {
            makeVertices();
            event.window()->repaint();
        }
    }

protected:
    glow::ref_ptr<glow::Texture> m_texture;
    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    glow::ref_ptr<glow::Buffer> m_vbo;
    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::FrameBufferObject> m_fbo;
    glow::ref_ptr<glow::Texture> m_colorTexture;
    glow::ref_ptr<glow::RenderBufferObject> m_depthBuffer;
    glow::ref_ptr<glowutils::ScreenAlignedQuad> m_quad;
    std::vector<Vertex> m_vertices;

    void makeVertices()
    {
        m_vertices.clear();
        for (int i=0; i<1000; ++i)
        {
            m_vertices.push_back(Vertex{
                glm::circularRand(1.f),
                glm::vec4(glm::sphericalRand(1.f), 1.f)
            });
        }

        m_vbo->setData(m_vertices);
    }
};


/** This example shows ... .
*/
int main(int /*argc*/, char* /*argv*/[])
{
    ContextFormat format;
    format.setVersion(3, 0);

    Window window;

    window.setEventHandler(new EventHandler());

    if (window.create(format, "Simple Texture Example"))
    {
        window.context()->setSwapInterval(Context::NoVerticalSyncronization);

        window.show();

        return MainLoop::run();
    }
    else
    {
        return 1;
    }
}
