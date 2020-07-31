//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/axis_info.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <sge/x11input/mouse/axis_code.hpp>
#include <sge/x11input/mouse/axis_info.hpp>
#include <sge/x11input/mouse/axis_value.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::axis_info
sge::x11input::mouse::axis_info(
	XIValuatorClassInfo const &_info,
	awl::backends::x11::display &_display
)
{
	fcppt::optional_string const name(
		sge::x11input::device::info::string_from_atom(
			_display,
			_info.label
		)
	);

	return
		sge::input::mouse::axis_info(
			sge::x11input::mouse::axis_code(
				name
			),
			// TODO(philipp)
			fcppt::optional_string{
				name
			}
		);
}
