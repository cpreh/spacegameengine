/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../alc_error_string.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sge::openal::alc_error_string(
	ALCenum const error
)
{
	switch (error)
	{
		case ALC_NO_ERROR:
			return FCPPT_TEXT("no error in openal (maybe somewhere else)");
		case ALC_INVALID_DEVICE:
			return FCPPT_TEXT("the device handle specifies an inaccessible driver/server");
		case ALC_INVALID_CONTEXT:
			return FCPPT_TEXT("the context argument does not name a valid context");
		case ALC_INVALID_ENUM:
			return FCPPT_TEXT("a token used is not valid, or not acceptable");
		case ALC_INVALID_VALUE:
			return FCPPT_TEXT("a value (e.g. attribute) is not valid, or not applicable");
		case ALC_OUT_OF_MEMORY:
			return FCPPT_TEXT("unable to allocate memory");
	}

	return FCPPT_TEXT("Unkown");
}
