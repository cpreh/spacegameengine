//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/element_name.hpp>
#include <sge/dinput/device/get_property_range.hpp>
#include <sge/dinput/device/range.hpp>
#include <sge/dinput/joypad/axis_code.hpp>
#include <sge/dinput/joypad/make_absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::input::joypad::absolute_axis_info
sge::dinput::joypad::make_absolute_axis_info(
	IDirectInputDevice8 &_device,
	DIDEVICEOBJECTINSTANCE const &_data
)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
	sge::dinput::device::range const range(
		sge::dinput::device::get_property_range(
			_device,
			_data,
			DIPROP_RANGE
		)
	);
FCPPT_PP_POP_WARNING

	return
		sge::input::joypad::absolute_axis_info(
			sge::dinput::joypad::axis_code(
				_data.dwOfs
			),
			sge::dinput::device::element_name(
				_data
			),
			sge::input::joypad::axis_min(
				range.min()
			),
			sge::input::joypad::axis_max(
				range.max()
			)
		);
}
