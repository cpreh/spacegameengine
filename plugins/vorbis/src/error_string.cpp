//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
