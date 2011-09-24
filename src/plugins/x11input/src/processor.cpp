/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../processor.hpp"
#include "../input_context.hpp"
#include "../input_method.hpp"
#include "../xi_2_1.hpp"
#include "../cursor/object.hpp"
#include "../device/id.hpp"
#include "../device/hierarchy_event.hpp"
#include "../device/make_manager_config.hpp"
#include "../device/multi_info.hpp"
#include "../device/object.hpp"
#include "../device/object_ptr.hpp"
#include "../device/parameters.hpp"
#include "../device/use.hpp"
#include "../joypad/device.hpp"
#include "../joypad/is_usable.hpp"
#include "../keyboard/device.hpp"
#include "../mouse/device.hpp"
#include <sge/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/instance_shared_ptr.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/operator/self.hpp>
#include <algorithm>
#include <utility>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::processor::processor(
	sge::window::instance_ptr const _window,
	awl::backends::x11::system::event::opcode const _opcode,
	x11input::xi_2_1 const _supports_xi_2_1
)
:
	window_(_window),
	opcode_(_opcode),
	x11_window_(
		fcppt::dynamic_pointer_cast<
			awl::backends::x11::window::instance
		>(
			_window->awl_instance()
		)
	),
	window_event_processor_(
		dynamic_cast<
			awl::backends::x11::window::event::processor &
		>(
			*_window->awl_window_event_processor()
		)
	),
	system_event_processor_(
		dynamic_cast<
			awl::backends::x11::system::event::processor &
		>(
			*_window->awl_system_event_processor()
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
	raw_demuxer_(
		system_event_processor_,
		opcode_,
		awl::backends::x11::window::instance_shared_ptr(
			awl::backends::x11::window::root(
				x11_window_->display(),
				x11_window_->screen()
			)
		),
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
		*x11_window_
	),
	invisible_cursor_(
		x11_window_->display(),
		invisible_pixmap_
	),
	input_method_(
		fcppt::make_unique_ptr<
			x11input::input_method
		>(
			fcppt::ref(
				x11_window_->display()
			),
			x11_window_->class_hint()
		)
	),
	input_context_(
		fcppt::make_unique_ptr<
			x11input::input_context
		>(
			input_method_->get(),
			input_method_->class_hint(),
			fcppt::ref(
				*x11_window_
			)
		)
	),
	keyboards_(),
	mice_(),
	cursors_(),
	joypads_(),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	device_manager_(
		fcppt::assign::make_container<
			device::manager_config_map
		>(
			std::make_pair(
				x11input::device::use(
					XIMasterKeyboard
				),
				device::make_manager_config(
					keyboards_,
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
				device::make_manager_config(
					cursors_,
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
				device::make_manager_config(
					mice_,
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
				device::make_manager_config(
					joypads_,
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
					FocusIn,
					std::tr1::bind(
						&processor::on_enter,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				window_event_processor_.register_callback(
					FocusOut,
					std::tr1::bind(
						&processor::on_leave,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
	x11input::device::multi_info const current_devices(
		x11_window_->display(),
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

sge::input::keyboard::device_vector const
sge::x11input::processor::keyboards() const
{
	return
		input::keyboard::device_vector(
			keyboards_.begin(),
			keyboards_.end()
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

sge::input::mouse::device_vector const
sge::x11input::processor::mice() const
{
	return
		input::mouse::device_vector(
			mice_.begin(),
			mice_.end()
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

sge::input::cursor::object_vector const
sge::x11input::processor::cursors() const
{
	return
		input::cursor::object_vector(
			cursors_.begin(),
			cursors_.end()
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

sge::input::joypad::device_vector const
sge::x11input::processor::joypads() const
{
	return
		input::joypad::device_vector(
			joypads_.begin(),
			joypads_.end()
		);
}

sge::window::instance_ptr const
sge::x11input::processor::window() const
{
	return window_;
}

sge::x11input::device::parameters const
sge::x11input::processor::device_parameters(
	x11input::device::id const _id
)
{
	return
		x11input::device::parameters(
			_id,
			opcode_,
			*x11_window_,
			window_demuxer_,
			raw_demuxer_
		);
}

sge::x11input::keyboard::device_ptr const
sge::x11input::processor::create_keyboard(
	x11input::device::id const _id
)
{
	return
		fcppt::make_shared_ptr<
			x11input::keyboard::device
		>(
			this->device_parameters(
				_id
			),
			fcppt::ref(
				*input_context_
			)
		);
}

sge::x11input::mouse::device_ptr const
sge::x11input::processor::create_mouse(
	x11input::device::id const _id
)
{
	return
		fcppt::make_shared_ptr<
			x11input::mouse::device
		>(
			this->device_parameters(
				_id
			)
		);
}

sge::x11input::cursor::object_ptr const
sge::x11input::processor::create_cursor(
	x11input::device::id const _id
)
{
	return
		fcppt::make_shared_ptr<
			x11input::cursor::object
		>(
			this->device_parameters(
				_id
			),
			invisible_cursor_.get()
		);
}

sge::x11input::joypad::device_ptr const
sge::x11input::processor::create_joypad(
	x11input::device::id const _id
)
{
	return
		joypad::is_usable(
			x11_window_->display(),
			_id
		)
		?
			fcppt::make_shared_ptr<
				x11input::joypad::device
			>(
				this->device_parameters(
					_id
				)
			)
		:
			x11input::joypad::device_ptr()
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
sge::x11input::processor::on_enter(
	awl::backends::x11::window::event::object const &
)
{
	raw_demuxer_.active(
		true
	);

	this->for_each_cursor(
		&x11input::cursor::object::on_enter
	);
}

void
sge::x11input::processor::on_leave(
	awl::backends::x11::window::event::object const &
)
{
	raw_demuxer_.active(
		false
	);

	this->for_each_cursor(
		&x11input::cursor::object::on_leave
	);
}

template<
	typename Function
>
void
sge::x11input::processor::for_each_cursor(
	Function const &_function
)
{
	std::for_each(
		cursors_.begin(),
		cursors_.end(),
		boost::phoenix::bind(
			_function,
			*boost::phoenix::arg_names::_1
		)
	);
}
