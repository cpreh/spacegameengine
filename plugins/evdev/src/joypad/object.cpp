//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/conditional_event.hpp>
#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/absolute_axis/make_event.hpp>
#include <sge/evdev/joypad/button/make_event.hpp>
#include <sge/evdev/joypad/ff/effect.hpp>
#include <sge/evdev/joypad/relative_axis/make_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::object::object(
	sge::evdev::device::fd_unique_ptr &&_fd,
	std::filesystem::path const &_path,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	sge::evdev::joypad::info const &_info
)
:
	sge::input::joypad::device{},
	sge::evdev::device::object{
		std::move(
			_fd
		),
		_processor,
		_path
	},
	fcppt::enable_shared_from_this<
		sge::evdev::joypad::object
	>{},
	window_{
		_window
	},
	info_{
		_info
	}
{
}

sge::evdev::joypad::object::~object()
{
}

sge::window::object &
sge::evdev::joypad::object::window() const
{
	return
		window_;
}

sge::input::joypad::info const &
sge::evdev::joypad::object::info() const
{
	return
		info_.input_info();
}

awl::event::optional_base_unique_ptr
sge::evdev::joypad::object::process_event(
	sge::evdev::device::event const &_event
)
{
	switch(
		_event.get().type
	)
	{
	case EV_ABS:
		return
			sge::evdev::device::conditional_event(
				sge::input::joypad::shared_ptr{
					this->fcppt_shared_from_this()
				},
				_event,
				info_.event_map().absolute_axis(),
				info_.input_info().absolute_axes(),
				&sge::evdev::joypad::absolute_axis::make_event
			);
	case EV_KEY:
		return
			sge::evdev::device::conditional_event(
				sge::input::joypad::shared_ptr{
					this->fcppt_shared_from_this()
				},
				_event,
				info_.event_map().buttons(),
				info_.input_info().buttons(),
				&sge::evdev::joypad::button::make_event
			);
	case EV_REL:
		return
			sge::evdev::device::conditional_event(
				sge::input::joypad::shared_ptr{
					this->fcppt_shared_from_this()
				},
				_event,
				info_.event_map().relative_axis(),
				info_.input_info().relative_axes(),
				&sge::evdev::joypad::relative_axis::make_event
			);
	}

	return
		awl::event::optional_base_unique_ptr{};
}

sge::input::joypad::ff::effect_unique_ptr
sge::evdev::joypad::object::create_ff_effect(
	sge::input::joypad::ff::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::joypad::ff::effect
		>(
			fcppt::make_unique_ptr<
				sge::evdev::joypad::ff::effect
			>(
				this->fd(),
				info_.event_map().buttons(),
				_parameters
			)
		);
}
