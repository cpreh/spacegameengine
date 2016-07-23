/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/dinput/create_dinput.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/processor.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/joypad/device.hpp>
#include <sge/dinput/keyboard/device.hpp>
#include <sge/dinput/mouse/device.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/backends/windows/lparam.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/post_message.hpp>
#include <awl/backends/windows/wparam.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/system/event/handle_callback.hpp>
#include <awl/backends/windows/system/event/processor.hpp>
#include <awl/backends/windows/window/has_focus.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::dinput::processor::processor(
	fcppt::log::object &_log,
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
:
	log_{
		_log
	},
	dinput_(
		sge::dinput::create_dinput()
	),
	windows_window_(
		fcppt::cast::dynamic_cross_exn<
			awl::backends::windows::window::object &
		>(
			_window.awl_object()
		)
	),
	event_processor_(
		fcppt::cast::dynamic_exn<
			awl::backends::windows::window::event::processor &
		>(
			_window.awl_window_event_processor()
		)
	),
	system_processor_(
		fcppt::cast::dynamic_exn<
			awl::backends::windows::system::event::processor &
		>(
			_window_system.awl_system_event_processor()
		)
	),
	devices_(),
	event_handle_(
		system_processor_.create_event_handle()
	),
	has_focus_(
		false
	),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	init_message_(
		system_processor_
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::message_type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_SETFOCUS
				),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::dinput::processor::on_focus_in,
						this,
						std::placeholders::_1
					)
				}
			),
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::message_type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_KILLFOCUS
				),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::dinput::processor::on_focus_out,
						this,
						std::placeholders::_1
					)
				}
			),
			event_processor_.register_callback(
				init_message_.type(),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::dinput::processor::on_init,
						this,
						std::placeholders::_1
					)
				}
			),
			system_processor_.register_handle_callback(
				awl::backends::windows::system::event::handle_callback{
					std::bind(
						&sge::dinput::processor::on_handle_ready,
						this
					)
				}
			)
		)
	)
{
	awl::backends::windows::post_message(
		windows_window_.hwnd(),
		init_message_.type(),
		awl::backends::windows::wparam(
			0u
		),
		awl::backends::windows::lparam(
			0
		)
	);
}
FCPPT_PP_POP_WARNING

sge::dinput::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			keyboard_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			keyboard_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			mouse_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			mouse_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::focus_discover_callback(
	sge::input::focus::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::focus_remove_callback(
	sge::input::focus::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			joypad_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::dinput::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			joypad_remove_.connect(
				_callback
			)
		};
}

awl::backends::windows::window::event::return_type
sge::dinput::processor::on_focus_in(
	awl::backends::windows::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus in")
	);

	has_focus_ =
		sge::dinput::has_focus(
			true
		);

	this->for_each_device(
		std::bind(
			&sge::dinput::device::object::acquire,
			std::placeholders::_1
		)
	);

	return
		awl::backends::windows::window::event::return_type();
}

awl::backends::windows::window::event::return_type
sge::dinput::processor::on_focus_out(
	awl::backends::windows::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus out")
	);

	has_focus_ =
		sge::dinput::has_focus(
			false
		);

	this->for_each_device(
		std::bind(
			&sge::dinput::device::object::unacquire,
			std::placeholders::_1
		)
	);

	return
		awl::backends::windows::window::event::return_type();
}

void
sge::dinput::processor::on_handle_ready()
{
	this->for_each_device(
		std::bind(
			&sge::dinput::device::object::dispatch,
			std::placeholders::_1
		)
	);
}

awl::backends::windows::window::event::return_type
sge::dinput::processor::on_init(
	awl::backends::windows::window::event::object const &
)
{
	if(
		awl::backends::windows::window::has_focus(
			windows_window_
		)
	)
		has_focus_ =
			sge::dinput::has_focus(
				true
			);

	if(
		dinput_->EnumDevices(
			DI8DEVCLASS_ALL,
			enum_devices_callback,
			this,
			DIEDFL_ATTACHEDONLY
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("DirectInput Enumeration failed!")
		);

	return
		awl::backends::windows::window::event::return_type(
			0u
		);
}

template<
	typename Function
>
void
sge::dinput::processor::for_each_device(
	Function const &_function
)
{
	std::for_each(
		devices_.begin(),
		devices_.end(),
		_function
	);
}

template<
	typename DiscoverEvent,
	typename Ptr
>
void
sge::dinput::processor::add_device(
	fcppt::signal::object<
		void(
			DiscoverEvent const &
		)
	> &_signal,
	Ptr _ptr
)
{
	_signal(
		DiscoverEvent(
			*_ptr
		)
	);

	devices_.push_back(
		fcppt::unique_ptr_to_base<
			sge::dinput::device::object
		>(
			std::move(
				_ptr
			)
		)
	);

	devices_.back()->acquire();
}

BOOL
sge::dinput::processor::enum_devices_callback(
	LPCDIDEVICEINSTANCE _ddi,
	LPVOID _state
)
{
	sge::dinput::processor &instance(
		*fcppt::cast::from_void_ptr<
			sge::dinput::processor *
		>(
			_state
		)
	);

	DWORD const dev_type(
		_ddi->dwDevType
		& 0xFF
	);

	fcppt::string const product_name(
		_ddi->tszProductName
	);

	sge::dinput::device::parameters const parameters(
		*instance.dinput_,
		product_name,
		_ddi->guidInstance,
		instance.windows_window_,
		*instance.event_handle_
	);

	switch(
		dev_type
	)
	{
	case DI8DEVTYPE_KEYBOARD:
		instance.add_device(
			instance.keyboard_discover_,
			fcppt::make_unique_ptr<
				sge::dinput::keyboard::device
			>(
				parameters
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		instance.add_device(
			instance.mouse_discover_,
			fcppt::make_unique_ptr<
				sge::dinput::mouse::device
			>(
				parameters
			)
		);
		break;
	case DI8DEVTYPE_JOYSTICK:
		instance.add_device(
			instance.joypad_discover_,
			fcppt::make_unique_ptr<
				sge::dinput::joypad::device
			>(
				parameters
			)
		);
		break;
	}

	return
		DIENUM_CONTINUE;
}
