//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/al.hpp>
#include <sge/openal/error_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sge::openal::error_string(
	ALenum const _error
)
{
	switch(
		_error
	)
	{
	case AL_NO_ERROR:
		return FCPPT_TEXT("no error in openal (maybe somewhere else)");
	case AL_INVALID_NAME:
		return FCPPT_TEXT("invalid name parameter");
	case AL_INVALID_ENUM:
		return FCPPT_TEXT("invalid parameter");
	case AL_INVALID_VALUE:
		return FCPPT_TEXT("invalid enum parameter value");
	case AL_INVALID_OPERATION:
		return FCPPT_TEXT("illegal call");
	case AL_OUT_OF_MEMORY:
		return FCPPT_TEXT("unable to allocate memory");
	default:
		return FCPPT_TEXT("Unknown");
	}
}
