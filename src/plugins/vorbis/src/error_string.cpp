/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/vorbis/error_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/codec.h>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::vorbis::error_string(
	int const _code
)
{
	switch(
		_code
	)
	{
	case OV_EREAD:
		return
			FCPPT_TEXT("a read from a media has returned an error");
	case OV_ENOTVORBIS:
		return
			FCPPT_TEXT("bitstream does not contain any vorbis data");
	case OV_EVERSION:
		return
			FCPPT_TEXT("vorbis version mismatch");
	case OV_EBADHEADER:
		return
			FCPPT_TEXT("invalid vorbis bitstream header");
	case OV_EFAULT:
		return
			FCPPT_TEXT("Internal logic fault (bug or heap/stack corruption)");
	case OV_ENOSEEK:
		return
			FCPPT_TEXT("bitstream is not seekable.");
	default:
		return
			FCPPT_TEXT("unknown ogg error");
	}
}
