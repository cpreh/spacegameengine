//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/exception.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/posix/processor_ref.hpp>
#include <fcppt/error_code_to_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/make_directory_range.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <system_error>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::map
sge::evdev::joypad::init(
	fcppt::log::object &_log,
	sge::window::object_ref const _window,
	awl::backends::posix::processor_ref const _processor,
	std::filesystem::path const &_path
)
{
	return
		fcppt::algorithm::map_optional<
			sge::evdev::joypad::map
		>(
			fcppt::either::to_exception(
				fcppt::filesystem::make_directory_range(
					_path,
					std::filesystem::directory_options::none
				),
				[](
					std::error_code const _error
				)
				{
					return
						sge::input::exception{
							FCPPT_TEXT("Cannot access joystick directory: ")
							+
							fcppt::error_code_to_string(
								_error
							)
						};
				}
			),
			[
				&_log,
				_window,
				&_processor
			](
				std::filesystem::path const &_cur
			)
			{
				return
					fcppt::optional::map(
						sge::evdev::joypad::create(
							_log,
							_window,
							_processor,
							_cur
						),
						[](
							sge::evdev::joypad::shared_ptr const &_ptr
						)
						{
							return
								sge::evdev::joypad::map::value_type{
									_ptr->posix_fd(),
									_ptr
								};
						}
					);
			}
		);
}
