//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/init.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <vector>
#include <fcppt/config/external_end.hpp>


std::vector<
	sge::sdlinput::joypad::shared_ptr
>
sge::sdlinput::joypad::init(
	sge::window::object &_window
)
{
	return
		fcppt::algorithm::map_optional<
			std::vector<
				sge::sdlinput::joypad::shared_ptr
			>
		>(
			fcppt::make_int_range_count(
				SDL_NumJoysticks()
			),
			[
				&_window
			](
				int const _index
			)
			{
				typedef
				fcppt::optional::object<
					sge::sdlinput::joypad::shared_ptr
				>
				result_type;

				try
				{
					return
						result_type{
							fcppt::make_shared_ptr<
								sge::sdlinput::joypad::device
							>(
								_window,
								sge::sdlinput::joypad::device_id{
									_index
								}
							)
						};
				}
				catch(
					sge::input::exception const &_error
				)
				{
					// TODO: Add logging
					return
						result_type{};
				}
			}
		);
}
