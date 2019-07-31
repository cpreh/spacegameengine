//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/const_optional_ref.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::info::single::single(
	awl::backends::x11::display &_display,
	sge::x11input::device::id const _id
)
:
	info_base_(
		_display
	),
	info_(
		fcppt::optional::deref(
			fcppt::algorithm::find_if_opt(
				info_base_,
				[
					_id
				](
					XIDeviceInfo const &_info
				)
				{
					return
						_info.deviceid
						==
						_id.get();
				}
			)
		)
	)
{
}

sge::x11input::device::info::single::~single()
{
}

sge::x11input::device::info::const_optional_ref
sge::x11input::device::info::single::get() const
{
	return
		info_;
}
