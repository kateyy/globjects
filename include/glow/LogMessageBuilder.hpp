#pragma once

#include <cassert>

namespace glow
{

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(Uniform<T>* uniform)
{
    assert(uniform != nullptr);

    *this << static_cast<AbstractUniform*>(uniform) << " " << uniform->value();
}

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<< (T * t_pointer)
{
	return *this << static_cast<void*>(t_pointer);
}

} // namespace glow
