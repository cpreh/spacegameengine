//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/valuator/any.hpp>
#include <sge/x11input/device/valuator/make_absolute.hpp>
#include <sge/x11input/device/valuator/make_any.hpp>
#include <sge/x11input/device/valuator/relative.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::valuator::any
sge::x11input::device::valuator::make_any(
	XIValuatorClassInfo const &_info
)
{
	switch(
		_info.mode
	)
	{
	case XIModeAbsolute:
		return
			sge::x11input::device::valuator::any{
				sge::x11input::device::valuator::make_absolute(
					_info
				)
			};
	case XIModeRelative:
		return
			sge::x11input::device::valuator::any{
				sge::x11input::device::valuator::relative{}
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
