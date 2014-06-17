#pragma once

#include <string>
#include <vector>
#include <functional>

#include <glbinding/types.h>

#include <glow/glow_api.h>

namespace glow {

class DebugMessage;

/** \brief Handles occuring OpenGL errors.

    The handling of OpenGL errors can be turned on using enable() and turned off
    using disable(). If glow is compiled with CMake flag
    -DOPTION_ERRORS_AS_EXCEPTION = On, then occuring OpenGL debug messages and
    errors get handled by throwing an exception.

    Errors will be handled as follows.
    If the CMake flag is Off, then a message with the error will be printed on
    the command line or the device connected with the ConsoleLogger. To provide
    meaningful stack traces during exception handling, the OpenGL errors should
    be handled synchroneous, which can be turned on using setSynchroneous().
    Instead of printing the error or throwing an exception, a user defined
    callback can be set which gets called for every occuring OpenGL error using
    addCallback().

    Debug messages can only be obtained using the gl::glARB_debug_output extension,
    which is in the OpenGL 4.3 Core Profile. Occuring OpenGL debug messages can
    be filtered using enableMessage(), enableMessages(), disableMessage() and
    disableMessages().

    \see ConsoleLogger
    \see http://www.opengl.org/registry/specs/ARB/debug_output.txt
 */
namespace debugmessageoutput {

using Callback = std::function<void(const DebugMessage &)>;

/** Sets up a context specific debug message error callback that outputs
    every incomming warning/error message generated by the driver.

    To avoid performance loss (even in DEBUG mode) this needs to be set
    manually for every context required. Further, in DEBUG, the default
    global gl error checking needs to be disabled manually.

    Note: this requires the GL_ARB_debug_output extension. Or at least a
    4.3 core profile. The output can be locally disabled via enable() and
    disable() - this sets DEBUG_OUTPUT_SYNCHRONOUS_ARB.
 */
GLOW_API void enable(bool synchronous = true);
GLOW_API void disable();

GLOW_API void setCallback(Callback callback);
GLOW_API void addCallback(Callback callback);

GLOW_API void setSynchronous(bool synchronous);

GLOW_API void insertMessage(gl::GLenum source, gl::GLenum type, gl::GLuint id, gl::GLenum severity, gl::GLsizei length, const char * message);
GLOW_API void insertMessage(gl::GLenum source, gl::GLenum type, gl::GLuint id, gl::GLenum severity, const std::string & message);
GLOW_API void insertMessage(const DebugMessage & message);

GLOW_API void enableMessage(gl::GLenum source, gl::GLenum type, gl::GLenum severity, gl::GLuint id);
GLOW_API void enableMessages(gl::GLenum source, gl::GLenum type, gl::GLenum severity, gl::GLsizei count, const gl::GLuint * ids);
GLOW_API void enableMessages(gl::GLenum source, gl::GLenum type, gl::GLenum severity, const std::vector<gl::GLuint> & ids);

GLOW_API void disableMessage(gl::GLenum source, gl::GLenum type, gl::GLenum severity, gl::GLuint id);
GLOW_API void disableMessages(gl::GLenum source, gl::GLenum type, gl::GLenum severity, gl::GLsizei count, const gl::GLuint * ids);
GLOW_API void disableMessages(gl::GLenum source, gl::GLenum type, gl::GLenum severity, const std::vector<gl::GLuint> & ids);

GLOW_API void controlMessages(gl::GLenum source, gl::GLenum type, gl::GLenum severity, gl::GLsizei count, const gl::GLuint * ids, gl::GLboolean enabled);

} // namespace debugmessageoutput

} // namespace glow
