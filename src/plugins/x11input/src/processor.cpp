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


#include <sge/log/global.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/x11input/create_parameters.hpp>
#include <sge/x11input/input_context.hpp>
#include <sge/x11input/input_method.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/xi_2_1.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/device/hierarchy_event.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <sge/x11input/device/manager/make_config.hpp>
#include <sge/x11input/joypad/device.hpp>
#include <sge/x11input/joypad/is_usable.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <awl/backends/x11/window/event/type.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::processor::processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system,
	awl::backends::x11::system::event::opcode const _opcode,
	x11input::xi_2_1 const _supports_xi_2_1
)
:
	opcode_(
		_opcode
	),
	x11_window_(
		dynamic_cast<
			awl::backends::x11::window::instance const &
		>(
			_window.awl_instance()
		)
	),
	window_event_processor_(
		dynamic_cast<
			awl::backends::x11::window::event::processor &
		>(
			_window.awl_window_event_processor()
		)
	),
	system_event_processor_(
		dynamic_cast<
			awl::backends::x11::system::event::processor &
		>(
			_window_system.awl_system_event_processor()
		)
	),
	window_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		device::demuxer_enabled(
			true
		)
	),
	root_window_(
		awl::backends::x11::window::root(
			x11_window_.display(),
			x11_window_.screen()
		)
	),
	raw_demuxer_(
		system_event_processor_,
		opcode_,
		*root_window_,
		device::demuxer_enabled(
			false
		)
	),
	hierarchy_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		device::demuxer_enabled(
			true
		)
	),
	invisible_pixmap_(
		x11_window_
	),
	invisible_cursor_(
		x11_window_.display(),
		invisible_pixmap_
	),
	input_method_(
		fcppt::make_unique_ptr<
			x11input::input_method
		>(
			fcppt::ref(
				x11_window_.display()
			),
			x11_window_.class_hint()
		)
	),
	input_context_(
		fcppt::make_unique_ptr<
			x11input::input_context
		>(
			input_method_->get(),
			input_method_->class_hint(),
			fcppt::cref(
				x11_window_
			)
		)
	),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	device_manager_(
		x11_window_.display(),
		fcppt::assign::make_container<
			device::manager::config_map
		>(
			std::make_pair(
				x11input::device::use(
					XIMasterKeyboard
				),
				device::manager::make_config<
					sge::x11input::keyboard::device
				>(
					keyboard_discover_,
					keyboard_remove_,
					std::tr1::bind(
						&x11input::processor::create_keyboard,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			std::make_pair(
				x11input::device::use(
					XIMasterPointer
				),
				device::manager::make_config<
					sge::x11input::cursor::object
				>(
					cursor_discover_,
					cursor_remove_,
					std::tr1::bind(
						&x11input::processor::create_cursor,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			std::make_pair(
				x11input::device::use(
					_supports_xi_2_1.get()
					?
						XISlavePointer
					:
						XIMasterPointer
				),
				device::manager::make_config<
					sge::x11input::mouse::device
				>(
					mouse_discover_,
					mouse_remove_,
					std::tr1::bind(
						&x11input::processor::create_mouse,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			std::make_pair(
				x11input::device::use(
					XIFloatingSlave
				),
				device::manager::make_config<
					sge::x11input::joypad::device
				>(
					joypad_discover_,
					joypad_remove_,
					std::tr1::bind(
						&x11input::processor::create_joypad,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	cursor_manager_(),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				hierarchy_demuxer_.register_callback(
					awl::backends::x11::system::event::type(
						XI_HierarchyChanged
					),
					sge::x11input::device::id(
						XIAllDevices
					),
					std::tr1::bind(
						&processor::on_hierarchy_changed,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				window_event_processor_.register_callback(
					awl::backends::x11::window::event::type(
						FocusIn
					),
					std::tr1::bind(
						&processor::on_focus_in,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				window_event_processor_.register_callback(
					awl::backends::x11::window::event::type(
						FocusOut
					),
					std::tr1::bind(
						&processor::on_focus_out,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				window_event_processor_.register_callback(
					awl::backends::x11::window::event::type(
						LeaveNotify
					),
					std::tr1::bind(
						&processor::on_leave,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				cursor_discover_.connect(
					std::tr1::bind(
						&x11input::cursor::manager::discover,
						&cursor_manager_,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				cursor_remove_.connect(
					std::tr1::bind(
						&x11input::cursor::manager::remove,
						&cursor_manager_,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
	x11input::device::info::multi const current_devices(
		x11_window_.display(),
		x11input::device::id(
			XIAllDevices
		)
	);

	for(
		int index = 0;
		index < current_devices.size();
		++index
	)
		device_manager_.initial(
			current_devices[
				index
			]
		);
}

sge::x11input::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_discover_callback(
	input::keyboard::discover_callback const &_callback
)
{
	return
		keyboard_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_remove_callback(
	input::keyboard::remove_callback const &_callback
)
{
	return
		keyboard_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_discover_callback(
	input::mouse::discover_callback const &_callback
)
{
	return
		mouse_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_remove_callback(
	input::mouse::remove_callback const &_callback
)
{
	return
		mouse_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::cursor_discover_callback(
	input::cursor::discover_callback const &_callback
)
{
	return
		cursor_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::cursor_remove_callback(
	input::cursor::remove_callback const &_callback
)
{
	return
		cursor_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::joypad_discover_callback(
	input::joypad::discover_callback const &_callback
)
{
	return
		joypad_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::joypad_remove_callback(
	input::joypad::remove_callback const &_callback
)
{
	return
		joypad_remove_.connect(
			_callback
		);
}

sge::x11input::device::parameters const
sge::x11input::processor::device_parameters(
	x11input::create_parameters const &_param
)
{
	return
		x11input::device::parameters(
			_param,
			opcode_,
			x11_window_,
			window_demuxer_,
			raw_demuxer_
		);
}

sge::x11input::keyboard::device_unique_ptr
sge::x11input::processor::create_keyboard(
	x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			x11input::keyboard::device
		>(
			this->device_parameters(
				_param
			),
			fcppt::ref(
				*input_context_
			)
		);
}

sge::x11input::mouse::device_unique_ptr
sge::x11input::processor::create_mouse(
	x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			x11input::mouse::device
		>(
			this->device_parameters(
				_param
			)
		);
}

sge::x11input::cursor::object_unique_ptr
sge::x11input::processor::create_cursor(
	x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			x11input::cursor::object
		>(
			this->device_parameters(
				_param
			),
			invisible_cursor_.get()
		);
}

sge::x11input::joypad::device_unique_ptr
sge::x11input::processor::create_joypad(
	x11input::create_parameters const &_param
)
{
	return
		joypad::is_usable(
			_param.info()
		)
		?
			fcppt::make_unique_ptr<
				x11input::joypad::device
			>(
				this->device_parameters(
					_param
				)
			)
		:
			x11input::joypad::device_unique_ptr()
		;
}

void
sge::x11input::processor::on_hierarchy_changed(
	sge::x11input::device::hierarchy_event const &_event
)
{
	for(
		int index = 0;
		index < _event.get().num_info;
		++index
	)
		device_manager_.change(
			_event.get().info[
				index
			]
		);
}

void
sge::x11input::processor::on_focus_in(
	awl::backends::x11::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11input: FocusIn")
	);

	raw_demuxer_.active(
		true
	);

	cursor_manager_.focus_in();
}

void
sge::x11input::processor::on_focus_out(
	awl::backends::x11::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11input: FocusOut")
	);

	raw_demuxer_.active(
		false
	);

	cursor_manager_.focus_out();
}

void
sge::x11input::processor::on_leave(
	awl::backends::x11::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11input: LeaveNotify")
	);

	cursor_manager_.leave();
}
