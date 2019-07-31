//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::info::multi::multi(
	awl::backends::x11::display &_display
)
:
	info_base_(
		_display,
		sge::x11input::device::id(
			XIAllDevices
		)
	)
{
}

sge::x11input::device::info::multi::~multi()
{
}

sge::x11input::device::info::multi::iterator
sge::x11input::device::info::multi::begin() const
{
	return
		info_base_.get();
}

sge::x11input::device::info::multi::iterator
sge::x11input::device::info::multi::end() const
{
	return
		info_base_.get()
		+
		info_base_.size();
}
