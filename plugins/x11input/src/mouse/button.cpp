//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::button
sge::x11input::mouse::button(
	XIDeviceEvent const  &_event,
	sge::input::mouse::button_info_container const &_info
)
{
	int const detail(
		_event.detail
	);

	FCPPT_ASSERT_PRE(
		detail > 0
	);

	sge::input::mouse::button_id const id(
		static_cast<
			sge::input::mouse::button_id::value_type
		>(
			detail - 1 // TODO(philipp): why?
		)
	);

	FCPPT_ASSERT_PRE(
		id < _info.size()
	);

	return
		sge::input::mouse::button(
			_info[
				id
			].code(),
			id
		);
}
