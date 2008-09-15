#include "../error_string.hpp"
#include "../openal.hpp"
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/audio/exception.hpp>

namespace
{
sge::string const error_string()
{
	ALenum const error = alGetError();
	switch (error)
	{
		case AL_NO_ERROR:
			return SGE_TEXT("no error (you shouldn't see this)");
		case AL_INVALID_NAME:
			return SGE_TEXT("invalid name parameter");
		case AL_INVALID_ENUM:
			return SGE_TEXT("invalid parameter");
		case AL_INVALID_VALUE:
			return SGE_TEXT("invalid enum parameter value");
		case AL_INVALID_OPERATION:
			return SGE_TEXT("illegal call");
		case AL_OUT_OF_MEMOTY:
			return SGE_TEXT("unable to allocate memory");
	}
	return SGE_TEXT("you really shouldn't see this");
}
}

void sge::openal::error_check(string const &file,string const &line)
{
	if (alGetError() != AL_NO_ERROR)
		throw audio::exception(SGE_TEXT("openal error: ")+file+SGE_TEXT(":")+line+SGE_TEXT(":")+error_string());
}
