//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/axis_value.hpp>
#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/update_accu.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <sge/x11input/mouse/axis_value.hpp>
#include <sge/x11input/mouse/axis_value_accu_pair.hpp>
#include <fcppt/preprocessor/todo.hpp>


sge::x11input::mouse::axis_value_accu_pair
sge::x11input::mouse::axis_value(
	sge::x11input::device::valuator::accu const _accu,
	sge::x11input::device::valuator::value const _value
)
{
	return
		sge::x11input::device::valuator::update_accu<
			sge::input::mouse::axis_value
		>(
			_accu,
			_value
		);
}
