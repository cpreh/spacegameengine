//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/optional_shared_ptr.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/exception.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <boost/algorithm/string/predicate.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::evdev::joypad::optional_shared_ptr
try_create(
	fcppt::log::object &_log,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	std::filesystem::path const &_path
)
{
	return
		fcppt::optional::bind(
			sge::evdev::device::create_fd(
				_log,
				_path
			),
			[
				&_log,
				&_window,
				&_processor,
				&_path
			](
				sge::evdev::device::fd_unique_ptr &&_fd
			)
			{
				try
				{
					sge::evdev::joypad::info const info(
						sge::evdev::joypad::make_info(
							*_fd
						)
					);

					return
						fcppt::optional::make_if(
							sge::evdev::joypad::is_joypad(
								info
							),
							[
								&info,
								&_path,
								&_window,
								&_processor,
								&_fd
							]{
								return
									sge::evdev::joypad::shared_ptr{
										fcppt::make_shared_ptr<
											sge::evdev::joypad::object
										>(
											std::move(
												_fd
											),
											_path,
											_window,
											_processor,
											info
										)
									};
							}
						);
				}
				catch(
					sge::input::exception const &_exception
				)
				{
					FCPPT_LOG_ERROR(
						_log,
						fcppt::log::out
							<<
							fcppt::filesystem::path_to_string(
								_path
							)
							<<
							FCPPT_TEXT(": ")
							<<
							_exception.string()
					)

					return
						sge::evdev::joypad::optional_shared_ptr{};
				}
			}
		);
}

}

sge::evdev::joypad::optional_shared_ptr
sge::evdev::joypad::create(
	fcppt::log::object &_log,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	std::filesystem::path const &_path
)
{
	return
		fcppt::optional::join(
			fcppt::optional::make_if(
				fcppt::not_(
					std::filesystem::is_directory(
						_path
					)
				)
				&&
				boost::algorithm::starts_with(
					_path.filename().string(),
					"event"
				),
				[
					&_log,
					&_window,
					&_processor,
					&_path
				]{
					return
						try_create(
							_log,
							_window,
							_processor,
							_path
						);
				}
			)
		);
}
