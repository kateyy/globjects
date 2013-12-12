#pragma once

#include <string>
#include <set>

#include <glow/glow.h>

#include <glow/Object.h>
#include <glow/Changeable.h>
#include <glow/ChangeListener.h>
#include <glow/ref_ptr.h>

// http://www.opengl.org/wiki/Shader

namespace glow 
{
class StringSource;
class Program;

/** \brief Encapsulates OpenGL shaders.
    
    A shader can be constructed using fromFile() or fromString() for either 
    shaders from a file or shaders from a string. The shader source later can
    be changed using setSource(). A shader can be attached to a program using 
    Program::attach(). A Shader subclasses either ChangeListener and Changeable
    to react to changing shader sources and to propagate this change to 
    ChangeListeners.

    \see Program
    \see ShaderSource
    \see ChangeListener
    \see Changeable
 */
class GLOW_API Shader : public Object, protected ChangeListener, public Changeable
{
	friend class Program;
    friend class ShaderCompiler;

public:
    static Shader * fromString(const GLenum type, const std::string & sourceString);

public:
	Shader(const GLenum type);
    Shader(const GLenum type, StringSource * source);

	virtual ~Shader();

	virtual void accept(ObjectVisitor& visitor);

	GLenum type() const;

    void setSource(StringSource * source);
	void setSource(const std::string & source);
    const StringSource* source() const;
    void updateSource();

    bool compile();
	bool isCompiled() const;
    void invalidate();

    GLint get(GLenum pname) const;
    bool checkCompileStatus() const;
	std::string infoLog() const;

    std::string typeString() const;

protected:
    void notifyChanged();


protected:
    static GLuint create(GLenum type);
    static void setSource(const Shader & shader, const std::string & source);

    std::string shaderString() const;

protected:
	GLenum m_type;
    ref_ptr<StringSource> m_source;

    bool m_compiled;
    bool m_compilationFailed;

};

} // namespace glow
