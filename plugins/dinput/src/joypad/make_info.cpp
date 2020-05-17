//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/guid_to_string.hpp>
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/joypad/enumerator.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/dinput/joypad/make_info.hpp>
#include <sge/dinput/joypad/ff/enum_effects.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>


sge::dinput::joypad::info
sge::dinput::joypad::make_info(
	IDirectInputDevice8 &_device,
	sge::input::info::name const &_name,
	GUID const &_guid
)
{
	sge::dinput::joypad::enumerator object(
		_device
	);

	sge::dinput::device::enumerate_objects(
		_device,
		object,
		DIDFT_AXIS
		|
		DIDFT_BUTTON
	);

	return
		sge::dinput::joypad::info(
			sge::input::joypad::info(
				sge::input::joypad::absolute_axis_info_container(
					sge::input::joypad::absolute_axis_info_container::vector{
						object.absolute_axis()
					}
				),
				sge::input::joypad::button_info_container(
					sge::input::joypad::button_info_container::vector{
						object.buttons()
					}
				),
				sge::input::joypad::relative_axis_info_container(
					sge::input::joypad::relative_axis_info_container::vector{
						object.relative_axis()
					}
				),
				sge::dinput::joypad::ff::enum_effects(
					_device
				),
				// TODO
				sge::input::info::name{
					_name
				},
				sge::input::info::unique_id(
					sge::dinput::guid_to_string(
						_guid
					)
				)
			),
			object.absolute_axis_map(),
			object.button_map(),
			object.relative_axis_map()
		);
}
