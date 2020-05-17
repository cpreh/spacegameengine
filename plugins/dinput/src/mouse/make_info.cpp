//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/mouse/enumerator.hpp>
#include <sge/dinput/mouse/info.hpp>
#include <sge/dinput/mouse/make_info.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info.hpp>
#include <fcppt/string.hpp>


sge::dinput::mouse::info
sge::dinput::mouse::make_info(
	IDirectInputDevice8 &_device,
	sge::input::info::name const &_name
)
{
	sge::dinput::mouse::enumerator object{};

	sge::dinput::device::enumerate_objects(
		_device,
		object,
		DIDFT_AXIS
		|
		DIDFT_BUTTON
	);

	return
		sge::dinput::mouse::info(
			sge::input::mouse::info(
				sge::input::mouse::axis_info_container(
					sge::input::mouse::axis_info_container::vector{
						object.axis()
					}
				),
				sge::input::mouse::button_info_container(
					sge::input::mouse::button_info_container::vector{
						object.buttons()
					}
				),
				// TODO
				sge::input::info::name{
					_name
				}
			),
			object.axis_map(),
			object.button_map()
		);
}
