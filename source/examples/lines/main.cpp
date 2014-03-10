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
layout (location=1) out vec4 outCount;

void main()
{
    outColor = color;
    outCount = vec4(1.0);
}

)";



const char* quadVertexShaderSource = R"(
#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout (location = 0) in vec2 a_vertex;
out vec2 v_uv;

void main()
{
    v_uv = a_vertex * 0.5 + 0.5;
    gl_Position = vec4(a_vertex, 0.0, 1.0);
}

)";

const char* quadFragmentShaderSource = R"(
#version 150
#extension GL_ARB_explicit_attrib_location : enable

uniform sampler2D colorTexture;
uniform sampler2D countTexture;

layout (location = 0) out vec4 fragColor;

in vec2 v_uv;

float kernel[25] = float[25](
    1.0, 4.0, 7.0, 4.0, 1.0,
    4.0, 16.0, 26.0, 16.0, 4.0,
    7.0, 26.0, 41.0, 26.0, 7.0,
    4.0, 16.0, 26.0, 16.0, 4.0,
    1.0, 4.0, 7.0, 4.0, 1.0
);

float filter(in ivec2 coord)
{
    float w = 0.0;

    const int SIZE_2 = 2;

    for (int y=-SIZE_2;y<=SIZE_2;++y)
    {
        for (int x=-SIZE_2;x<=SIZE_2;++x)
        {
            float k = kernel[(y+1)*SIZE_2+(x+1)];
            float count = texelFetch(countTexture, coord+ivec2(x,y), 0).r;

            w += k * count;
        }
    }

    return w/273.0;
}

vec3 col(in ivec2 coord)
{
    vec3 c = vec3(0.0);
    float tw = 0.0;

    const int SIZE_2 = 2;

    for (int y=-SIZE_2;y<=SIZE_2;++y)
    {
        for (int x=-SIZE_2;x<=SIZE_2;++x)
        {
            float count = texelFetch(countTexture, coord+ivec2(x,y), 0).r;
            vec3 color = texelFetch(colorTexture, coord+ivec2(x,y), 0).rgb;

            if (count>0.0)
            {
                float w = length(vec2(x,y));

                c += color/count*w;

                tw += w;
            }
        }
    }

    return c/tw;
}

void main()
{
    ivec2 size = textureSize(countTexture, 0);
    ivec2 coord = ivec2(v_uv*vec2(size));

    //float count = texelFetch(countTexture, coord, 0).r;
    //vec3 color = texture(colorTexture, v_uv).rgb/count;
    vec3 color = col(coord);
    //float f = filter(coord);
    //vec3 color = vec3(f>0.0?mix(0.5, 1.0, f):0.0, 0.0, 0.0);

    fragColor = vec4(color, 1.0);
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

        glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);

        //glClearColor(1.f, 1.f, 1.f, 1.f);
        glClearColor(0.f, 0.f, 0.f, 1.f);
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

        m_countTexture = new glow::Texture(GL_TEXTURE_2D);

        m_countTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        m_countTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        m_countTexture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_countTexture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        m_countTexture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        m_fbo = new glow::FrameBufferObject;
        m_fbo->attachTexture(GL_COLOR_ATTACHMENT0, m_colorTexture);
        m_fbo->attachTexture(GL_COLOR_ATTACHMENT1, m_countTexture);

        m_fbo->unbind();

        m_quadProgram = new glow::Program;
        m_quadProgram->attach(
            glow::Shader::fromString(GL_VERTEX_SHADER, quadVertexShaderSource),
            glow::Shader::fromString(GL_FRAGMENT_SHADER, quadFragmentShaderSource)
        );
        m_quadProgram->setUniform("colorTexture", 0);
        m_quadProgram->setUniform("countTexture", 1);
        m_quad = new glowutils::ScreenAlignedQuad(m_quadProgram);

        window.addTimer(0, 0);
    }

    virtual void finalize(Window & ) override
    {
        m_vao = nullptr;
        m_vbo = nullptr;
        m_program = nullptr;
        m_fbo = nullptr;
        m_quad = nullptr;
        m_quadProgram = nullptr;
    }

    virtual void framebufferResizeEvent(ResizeEvent & event) override
    {
        int width = event.width();
        int height = event.height();
    	int side = std::min<int>(width, height);

        glViewport((width - side) / 2, (height - side) / 2, side, side);
        CheckGLError();

        m_colorTexture->image2D(0, GL_RGBA8, glm::ivec2(width, height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        m_countTexture->image2D(0, GL_RGBA32F, glm::ivec2(width, height), 0, GL_RGBA, GL_FLOAT, nullptr);

        m_fbo->printStatus(true);
    }

    virtual void paintEvent(PaintEvent &) override
    {
        m_fbo->bind();

        m_fbo->setDrawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 });

        m_fbo->clear(GL_COLOR_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glBlendFunc(GL_ONE, GL_ONE);
        glBlendEquation(GL_FUNC_ADD);

        m_program->use();
        m_vao->drawArrays(GL_LINES, 0, (int)m_vertices.size());
        m_program->release();

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        m_fbo->unbind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CheckGLError();

        m_quadProgram->use();

        m_colorTexture->bindActive(GL_TEXTURE0);
        m_countTexture->bindActive(GL_TEXTURE1);

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
    glow::ref_ptr<glow::Texture> m_countTexture;
    glow::ref_ptr<glowutils::ScreenAlignedQuad> m_quad;
    glow::ref_ptr<glow::Program> m_quadProgram;
    std::vector<Vertex> m_vertices;

    void makeVertices()
    {
        m_vertices.clear();
        for (int i=0; i<2000; ++i)
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
