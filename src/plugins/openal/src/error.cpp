/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <sge/string.hpp>
#include <sge/audio/exception.hpp>

namespace
{
sge::string const alc_error_string(ALCenum const error)
{
	switch (error)
	{
		case ALC_NO_ERROR:
			return SGE_TEXT("no error in openal (maybe somewhere else)");
		case ALC_INVALID_DEVICE:
			return SGE_TEXT("the device handle specifies an inaccessible driver/server");
		case ALC_INVALID_CONTEXT:
			return SGE_TEXT("the context argument does not name a valid context");
		case ALC_INVALID_ENUM:
			return SGE_TEXT("a token used is not valid, or not acceptable");
		case ALC_INVALID_VALUE:
			return SGE_TEXT("a value (e.g. attribute) is not valid, or not applicable");
		case ALC_OUT_OF_MEMORY:
			return SGE_TEXT("unable to allocate memory");
	}

	if (!std::uncaught_exception())
		throw sge::audio::exception(
			sge::str(
				sge::format(SGE_TEXT("invalid alc error code: %1%")) % error));
	
	return SGE_TEXT("you shouldn't see this");
}

sge::string const error_string(ALenum const error)
{
	switch (error)
	{
		case AL_NO_ERROR:
			return SGE_TEXT("no error in openal (maybe somewhere else)");
		case AL_INVALID_NAME:
			return SGE_TEXT("invalid name parameter");
		case AL_INVALID_ENUM:
			return SGE_TEXT("invalid parameter");
		case AL_INVALID_VALUE:
			return SGE_TEXT("invalid enum parameter value");
		case AL_INVALID_OPERATION:
			return SGE_TEXT("illegal call");
		case AL_OUT_OF_MEMORY:
			return SGE_TEXT("unable to allocate memory");
	}

	if (!std::uncaught_exception())
		throw sge::audio::exception(
			sge::str(sge::format(SGE_TEXT("invalid openal error code: %1%")) % error));

	return SGE_TEXT("you shouldn't see this");
}
}

void sge::openal::error_check(string const &file,string const &line)
{
	ALenum const error = alGetError();
	if (error != AL_NO_ERROR)
		if (!std::uncaught_exception())
			throw audio::exception(str(format(SGE_TEXT("openal error %1%:%2%: %3%")) % file % line % error_string(error)));
}

void sge::openal::alc_error_check(ALCdevice * const device,string const &file,string const &line)
{
	ALCenum const error = alcGetError(device);

	if (error != ALC_NO_ERROR)
		if (!std::uncaught_exception())
			throw audio::exception(str(format(SGE_TEXT("alc error %1%:%2%: %3%")) % file % line % alc_error_string(error)));
}
