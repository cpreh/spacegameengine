//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/processor.hpp>
#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/remove.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/backends/posix/event.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/posix/processor_base.hpp>
#include <awl/event/base.hpp>
#include <awl/event/connection.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/map_values_copy.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::evdev::processor::processor(
	fcppt::log::object &_log,
	sge::window::object &_window
)
:
	sge::input::processor{},
	log_{
		_log
	},
	path_{
		"/dev/input"
	},
	window_{
		_window
	},
	processor_{
		fcppt::cast::dynamic_cross_exn<
			awl::backends::posix::processor_base &
		>(
			_window.system().awl_system().processor()
		).fd_processor()
	},
	dev_watch_{
		this->path_
	},
	dev_watch_connection_{
		this->processor_.register_fd(
			this->dev_watch_.fd()
		)
	},
	joypads_{
		sge::evdev::joypad::init(
			this->log_,
			this->window_,
			this->processor_,
			this->path_
		)
	},
	event_connection_{
		_window.system().event_handler(
			sge::window::system_event_function{
				[
					this
				](
					awl::event::base const &_event
				)
				{
					return
						this->system_event(
							_event
						);
				}
			}
		)
	}
{
}

sge::evdev::processor::~processor()
{
}

sge::window::object &
sge::evdev::processor::window() const
{
	return
		this->window_;
}

sge::input::cursor::container
sge::evdev::processor::cursors() const
{
	return
		sge::input::cursor::container{};
}

sge::input::focus::container
sge::evdev::processor::foci() const
{
	return
		sge::input::focus::container{};
}

sge::input::joypad::container
sge::evdev::processor::joypads() const
{
	return
		fcppt::algorithm::map<
			sge::input::joypad::container
		>(
			fcppt::container::map_values_copy<
				std::vector<
					sge::evdev::joypad::shared_ptr
				>
			>(
				this->joypads_
			),
			[](
				sge::evdev::joypad::shared_ptr &&_ptr
			)
			{
				return
					sge::input::joypad::shared_ptr{
						std::move(
							_ptr
						)
					};
			}
		);
}

sge::input::keyboard::container
sge::evdev::processor::keyboards() const
{
	return
		sge::input::keyboard::container{};
}

sge::input::mouse::container
sge::evdev::processor::mice() const
{
	return
		sge::input::mouse::container{};
}

awl::event::container
sge::evdev::processor::system_event(
	awl::event::base const &_event
)
{
	return
		fcppt::optional::from(
			fcppt::optional::map(
				fcppt::cast::dynamic<
					awl::backends::posix::event const
				>(
					_event
				),
				[
					this
				](
					fcppt::reference<
						awl::backends::posix::event const
					> const _posix_event
				)
				{
					return
						this->fd_event(
							_posix_event.get()
						);
				}
			),
			[]{
				return
					awl::event::container();
			}
		);
}

awl::event::container
sge::evdev::processor::fd_event(
	awl::backends::posix::event const &_event
)
{
	return
		_event.fd()
		==
		this->dev_watch_.fd()
		?
			fcppt::algorithm::map_optional<
				awl::event::container
			>(
				this->dev_watch_.on_event(),
				[
					this
				](
					sge::evdev::inotify::event const &_inotify_event
				)
				{
					return
						this->inotify_event(
							_inotify_event
						);
				}
			)
		:
			this->device_event(
				_event
			)
		;
}

awl::event::optional_base_unique_ptr
sge::evdev::processor::inotify_event(
	sge::evdev::inotify::event const &_event
)
{
	std::filesystem::path const file_path(
		this->path_
		/
		_event.filename()
	);

	switch(
		_event.event_type()
	)
	{
	case sge::evdev::inotify::event_type::add:
		return
			sge::evdev::joypad::add(
				this->log_,
				this->window_,
				this->processor_,
				this->joypads_,
				file_path
			);
	case sge::evdev::inotify::event_type::remove:
		return
			sge::evdev::joypad::remove(
				this->joypads_,
				file_path
			);
	case sge::evdev::inotify::event_type::attrib:
		return
			sge::evdev::joypad::attrib(
				this->log_,
				this->window_,
				this->processor_,
				this->joypads_,
				file_path
			);
	}

	return
		awl::event::optional_base_unique_ptr{};
}

awl::event::container
sge::evdev::processor::device_event(
	awl::backends::posix::event const &_event
)
{
	return
		fcppt::optional::from(
			fcppt::optional::map(
				fcppt::container::find_opt_mapped(
					this->joypads_,
					_event.fd()
				),
				[](
					fcppt::reference<
						sge::evdev::joypad::shared_ptr
					> const _joypad
				)
				{
					return
						_joypad.get()->on_event();
				}
			),
			[]{
				return
					awl::event::container{};
			}
		);
}
