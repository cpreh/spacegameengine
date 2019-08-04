//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <sge/sdlinput/joypad/make_info.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


sge::input::joypad::info
sge::sdlinput::joypad::make_info(
	SDL_Joystick &_joystick
)
{
	// TODO
	return
		sge::input::joypad::info{
			sge::input::joypad::absolute_axis_info_container{
				sge::input::joypad::absolute_axis_info_container::vector{}
			},
			sge::input::joypad::button_info_container{
				sge::input::joypad::button_info_container::vector{}
			},
			sge::input::joypad::relative_axis_info_container{
				sge::input::joypad::relative_axis_info_container::vector{}
			},
			sge::input::joypad::ff::type_field::null(),
			sge::input::info::name{
				fcppt::string{}
			},
			sge::input::info::unique_id{
				fcppt::string{}
			}
		};
}
