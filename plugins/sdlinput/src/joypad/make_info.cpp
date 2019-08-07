//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <sge/sdlinput/joypad/make_info.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <array>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::optional::object<
	std::string
>
get_name(
	SDL_Joystick &_joystick
)
{
	char const *const result{
		SDL_JoystickName(
			&_joystick
		)
	};

	return
		fcppt::optional::make_if(
			result
			!=
			nullptr,
			[
				result
			]{
				return
					std::string{
						result
					};
			}
		);
}

std::string
get_guid(
	SDL_Joystick &_joystick
)
{
	SDL_JoystickGUID const guid{
		SDL_JoystickGetGUID(
			&_joystick
		)
	};

	std::array<
		char,
		33
	> guid_string{};

	SDL_JoystickGetGUIDString(
		guid,
		guid_string.data(),
		fcppt::cast::size<
			int
		>(
			fcppt::cast::to_signed(
				guid_string.size()
			)
		)
	);

	return
		std::string{
			guid_string.data()
		};
}

sge::input::joypad::absolute_axis_info_container::vector::size_type
num_axes(
	SDL_Joystick &_joystick
)
{
	return
		fcppt::cast::to_unsigned(
			SDL_JoystickNumAxes(
				&_joystick
			)
		);
}

sge::input::joypad::relative_axis_info_container::vector::size_type
num_balls(
	SDL_Joystick &_joystick
)
{
	return
		fcppt::cast::to_unsigned(
			SDL_JoystickNumBalls(
				&_joystick
			)
		);
}

sge::input::joypad::button_info_container::vector::size_type
num_buttons(
	SDL_Joystick &_joystick
)
{
	return
		fcppt::cast::to_unsigned(
			SDL_JoystickNumButtons(
				&_joystick
			)
		);
}

sge::input::joypad::absolute_axis_info_container::vector::size_type
num_hats(
	SDL_Joystick &_joystick
)
{
	return
		fcppt::cast::to_unsigned(
			SDL_JoystickNumHats(
				&_joystick
			)
		);
}

}

sge::input::joypad::info
sge::sdlinput::joypad::make_info(
	SDL_Joystick &_joystick
)
{
	return
		sge::input::joypad::info{
			sge::input::joypad::absolute_axis_info_container{
				fcppt::container::join(
					sge::input::joypad::absolute_axis_info_container::vector{
						num_axes(
							_joystick
						),
						sge::input::joypad::absolute_axis_info{
							sge::input::joypad::axis_code::unknown,
							fcppt::optional_string{},
							sge::input::joypad::axis_min{
								-32768
							},
							sge::input::joypad::axis_max{
								32767
							}
						}
					},
					sge::input::joypad::absolute_axis_info_container::vector{
						num_hats(
							_joystick
						),
						sge::input::joypad::absolute_axis_info{
							sge::input::joypad::axis_code::x,
							fcppt::optional_string{},
							sge::input::joypad::axis_min{
								-1
							},
							sge::input::joypad::axis_max{
								1
							}
						}
					},
					sge::input::joypad::absolute_axis_info_container::vector{
						num_hats(
							_joystick
						),
						sge::input::joypad::absolute_axis_info{
							sge::input::joypad::axis_code::y,
							fcppt::optional_string{},
							sge::input::joypad::axis_min{
								-1
							},
							sge::input::joypad::axis_max{
								1
							}
						}
					}
				)
			},
			sge::input::joypad::button_info_container{
				sge::input::joypad::button_info_container::vector{
					num_buttons(
						_joystick
					),
					sge::input::joypad::button_info{
						fcppt::optional_string{}
					}
				}
			},
			sge::input::joypad::relative_axis_info_container{
				fcppt::container::join(
					sge::input::joypad::relative_axis_info_container::vector{
						num_balls(
							_joystick
						),
						sge::input::joypad::relative_axis_info{
							sge::input::joypad::axis_code::x,
							fcppt::optional_string{}
						}
					},
					sge::input::joypad::relative_axis_info_container::vector{
						num_balls(
							_joystick
						),
						sge::input::joypad::relative_axis_info{
							sge::input::joypad::axis_code::y,
							fcppt::optional_string{}
						}
					}
				)
			},
			// TODO
			sge::input::joypad::ff::type_field::null(),
			sge::input::info::name{
				fcppt::optional::maybe(
					get_name(
						_joystick
					),
					[]{
						return
							fcppt::string{};
					},
					[](
						std::string const &_name
					)
					{
						return
							fcppt::from_std_string(
								_name
							);
					}
				)
			},
			sge::input::info::unique_id{
				fcppt::from_std_string(
					get_guid(
						_joystick
					)
				)
			}
		};
}
