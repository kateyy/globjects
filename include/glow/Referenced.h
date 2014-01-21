#pragma once

#include <glow/glow.h>

namespace glow 
{

/**
 * \brief Superclass for all classes that use reference counting in glow.
 * The ref counter can be increased and decreased using ref() and unref().
 * If the ref counter decreases to zero, the referenced objects is deleted.
 * Referenced objects should not be copy constructed or assigned.
 */
class GLOW_API Referenced
{
public:
	Referenced();
	virtual ~Referenced();

    /**
     * Increment the number of references to this object.
     */
	void ref();
    /**
     * Decrement the number of references to this object.
     */
	void unref();
    /**
     * Returns the number of references to this object.
     */
	int refCounter() const;

protected:
	Referenced(const Referenced &);
	Referenced & operator=(const Referenced &);

private:
    /**
     * Keeps track of the references to this object.
     */
    int m_refCounter;
};

} // namespace glow
