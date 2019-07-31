//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/cursor/grab_error_to_string.hpp>
#include <awl/backends/x11/X.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sge::x11input::cursor::grab_error_to_string(
	int const _status
)
{
	switch(
		_status
	)
	{
	case AlreadyGrabbed:
		return
			FCPPT_TEXT("AlreadyGrabbed");
	case GrabNotViewable:
		return
			FCPPT_TEXT("GrabNotViewable");
	case GrabFrozen:
		return
			FCPPT_TEXT("GrabFrozen");
	case GrabInvalidTime:
		return
			FCPPT_TEXT("GrabInvalidTime");
	}

	return
		FCPPT_TEXT("Unknown");
}
