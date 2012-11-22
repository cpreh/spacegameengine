/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/processor.hpp>
#include <sge/dinput/cursor/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/joypad/device.hpp>
#include <sge/dinput/keyboard/device.hpp>
#include <sge/dinput/mouse/device.hpp>
#include <sge/dinput/create_dinput.hpp>
#include <sge/dinput/di.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/logger.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/backends/windows/event/lparam.hpp>
#include <awl/backends/windows/event/post_message.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/event/wparam.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/system/event/processor.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/window/has_focus.hpp>
#include <awl/window/event/focus_in_fwd.hpp>
#include <awl/window/event/focus_in_callback.hpp>
#include <awl/window/event/focus_out_fwd.hpp>
#include <awl/window/event/focus_out_callback.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::dinput::processor::processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
:
	dinput_(
		sge::dinput::create_dinput()
	),
	windows_window_(
		dynamic_cast<
			awl::backends::windows::window::object &
		>(
			_window.awl_object()
		)
	),
	event_processor_(
		dynamic_cast<
			awl::backends::windows::window::event::processor &
		>(
			_window.awl_window_event_processor()
		)
	),
	system_processor_(
		dynamic_cast<
			awl::backends::windows::system::event::processor &
		>(
			_window_system.awl_system_event_processor()
		)
	),
	devices_(),
	cursor_(
		fcppt::make_unique_ptr<
			sge::dinput::cursor::object
		>(
			fcppt::ref(
				event_processor_
			),
			fcppt::ref(
				windows_window_
			)
		)
	),
	event_handle_(
		system_processor_.create_event_handle()
	),
	acquired_(
		awl::window::has_focus(
			_window_system.awl_system(),
			_window.awl_object()
		)
	),
	cursor_discover_(),
	cursor_remove_(),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	init_message_(
		event_processor_
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				event_processor_.focus_in_callback(
					awl::window::event::focus_in_callback(
						std::tr1::bind(
							&dinput::processor::on_focus_in,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				event_processor_.focus_out_callback(
					awl::window::event::focus_out_callback(
						std::tr1::bind(
							&dinput::processor::on_focus_out,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				event_processor_.register_callback(
					init_message_.type(),
					std::tr1::bind(
						&dinput::processor::on_init,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				system_processor_.register_handle_callback(
					std::tr1::bind(
						&dinput::processor::on_handle_ready,
						this
					)
				)
			)
		)
	)
{
	awl::backends::windows::event::post_message(
		windows_window_.hwnd(),
		init_message_.type(),
		awl::backends::windows::event::wparam(
			0u
		),
		awl::backends::windows::event::lparam(
			0
		)
	);
}
FCPPT_PP_POP_WARNING

sge::dinput::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::dinput::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &_callback
)
{
	return
		keyboard_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &_callback
)
{
	return
		keyboard_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &_callback
)
{
	return
		mouse_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &_callback
)
{
	return
		mouse_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		cursor_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		cursor_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &_callback
)
{
	return
		joypad_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &_callback
)
{
	return
		joypad_remove_.connect(
			_callback
		);
}

void
sge::dinput::processor::on_focus_in(
	awl::window::event::focus_in const &
)
{
	FCPPT_LOG_DEBUG(
		sge::input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus in")
	);

	acquired_ = true;

	this->for_each_device(
		&sge::dinput::device::object::acquire
	);

	//cursor_->acquire();
}

void
sge::dinput::processor::on_focus_out(
	awl::window::event::focus_out const &
)
{
	FCPPT_LOG_DEBUG(
		sge::input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus out")
	);

	acquired_ = false;

	this->for_each_device(
		&sge::dinput::device::object::unacquire
	);

	cursor_->unacquire();
}

void
sge::dinput::processor::on_handle_ready()
{
	if(
		!acquired_
	)
		return;

	this->for_each_device(
		&dinput::device::object::dispatch
	);
}

awl::backends::windows::window::event::return_type
sge::dinput::processor::on_init(
	awl::backends::windows::window::event::object const &
)
{
	if(
		acquired_
	)
		cursor_->acquire();

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

	cursor_discover_(
		sge::input::cursor::discover_event(
			*cursor_
		)
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
		boost::phoenix::bind(
			_function,
			boost::phoenix::arg_names::arg1
		)
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

	fcppt::container::ptr::push_back_unique_ptr(
		devices_,
		fcppt::move(
			_ptr
		)
	);

	if(
		acquired_
	)
		devices_.back().acquire();
}

BOOL
sge::dinput::processor::enum_devices_callback(
	LPCDIDEVICEINSTANCE _ddi,
	LPVOID _state
)
{
	sge::dinput::processor &instance(
		*static_cast<
			dinput::processor *
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
		instance.dinput_.get(),
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

	return DIENUM_CONTINUE;
}
