#pragma once

#include <string>

#include <glbinding/types.h>

#include <glowbase/Referenced.h>

#include <glow/glow_api.h>

namespace glow {

class ObjectVisitor;

/**
 * Superclass of all wrapped OpenGL objects.
 * The superclass is Referenced so that each wrapped OpenGL object supports reference counting.
 * Subclasses should call the Object constructor passing a valid OpenGL object name (id) and a
 * flag whether this OpenGL object should be destroyed during the destructor.
 * The OpenGL name (id) that was provided in the constructor can be queried using id().
 * Additionally, an Object can have meaningful name wich can be get and set using name() and setName().
 */
class GLOW_API Object : public Referenced
{
    
public:
    virtual void accept(ObjectVisitor & visitor) = 0;

    gl::GLuint id() const;

    /**
     * Returns the raw OpenGL ID of this OpenGL object as a GLuint.
     */
	GLuint id() const;
    /**
     * Cast operator to cast this Object to a GLuint
     */
	operator GLuint() const;

	bool ownsGLObject() const;

    void takeOwnership();
    void releaseOwnership();

	const std::string & name() const;
	void setName(const std::string & name);
    bool hasName() const;

    
private:
    /**
     * Private default c'tor.
     */
    Object();
    /**
     * Private copy c'tor.
     */
    Object(const Object &);
    /**
     * Private assign operator.
     */
    Object & operator=(const Object &);

    void registerObject();
    void deregisterObject();

    
protected:
    Object(gl::GLuint id, bool takeOwnership = true);
    virtual ~Object();

protected:
    /**
     * The OpenGL id of this object as a GLuint
     */
	GLuint m_id;
    /**
     * The OpenGL id of this object as a GLuint *//** Flag that indicates if this object is responsible for another OpenGL object.
     */
	bool m_ownsGLObject;
    /**
     * The name of this object if set.
     */
    std::string m_name;
};

} // namespace glow
