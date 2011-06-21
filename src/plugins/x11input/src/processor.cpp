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
#include "../cursor/object.hpp"
#include "../device/hierarchy_event.hpp"
#include "../device/info.hpp"
#include "../device/object.hpp"
#include "../device/parameters.hpp"
#include "../keyboard/device.hpp"
#include "../mouse/device.hpp"
#include <sge/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/instance_shared_ptr.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::processor::processor(
	sge::window::instance_ptr const _window,
	awl::backends::x11::system::event::opcode const _opcode
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
		x11_window_
	),
	raw_demuxer_(
		system_event_processor_,
		opcode_,
		awl::backends::x11::window::instance_shared_ptr(
			awl::backends::x11::window::root(
				x11_window_->display(),
				x11_window_->screen()
			)
		)
	),
	hierarchy_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_
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
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				hierarchy_demuxer_.register_callback(
					awl::backends::x11::system::event::type(
						XI_HierarchyChanged
					),
					// TODO: this should be simplified a little
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
	x11input::device::info const current_devices(
		x11_window_->display(),
		XIAllDevices
	);

	for(
		int index = 0;
		index < current_devices.size();
		++index
	)
	{
		XIDeviceInfo const &device(
			current_devices[
				index
			]
		);

		x11input::device::parameters const param(
			this->device_parameters(
				x11input::device::id(
					device.deviceid
				)
			)
		);

		switch(
			device.use
		)
		{
		case XIMasterKeyboard:
			keyboards_.push_back(
				this->create_keyboard(
					param
				)
			);
			break;
		case XIMasterPointer:
		// FIXME: Use master pointers only for now
		// because slave pointers are unsuable with RawMotions
		//case XISlavePointer:
			mice_.push_back(
				this->create_mouse(
					param
				)
			);
		//	break;
		//case XIMasterPointer:
			cursors_.push_back(
				this->create_cursor(
					param
				)
			);
			break;
		}
	}
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

sge::window::instance_ptr const
sge::x11input::processor::window() const
{
	return window_;
}

sge::x11input::processor::device_vector const
sge::x11input::processor::devices() const
{
	// TODO: optimize this with a view
	device_vector ret(
		cursors_.begin(),
		cursors_.end()
	);

	fcppt::algorithm::append(
		ret,
		device_vector(
			mice_.begin(),
			mice_.end()
		)
	);

	return ret;
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
	x11input::device::parameters const &_param
) const
{
	return
		fcppt::make_shared_ptr<
			x11input::keyboard::device
		>(
			_param,
			fcppt::ref(
				*input_context_
			)
		);
}

sge::x11input::mouse::device_ptr const
sge::x11input::processor::create_mouse(
	x11input::device::parameters const &_param
) const
{
	return
		fcppt::make_shared_ptr<
			x11input::mouse::device
		>(
			_param
		);
}

sge::x11input::cursor::object_ptr const
sge::x11input::processor::create_cursor(
	x11input::device::parameters const &_param
) const
{
	return
		fcppt::make_shared_ptr<
			x11input::cursor::object
		>(
			_param,
			invisible_cursor_.get()
		);
}

void
sge::x11input::processor::on_hierarchy_changed(
	sge::x11input::device::hierarchy_event const &_event
)
{
	XIHierarchyEvent const &event(
		_event.get()
	);

	for(
		int index = 0;
		index < event.num_info;
		++index
	)
	{
		XIHierarchyInfo	const &info(
			event.info[
				index
			]
		);

		sge::x11input::device::id const device_id(
			info.deviceid
		);

		if(
			info.flags & XIMasterAdded
		)
		{
			x11input::device::parameters const param(
				this->device_parameters(
					device_id
				)
			);

			switch(
				info.use
			)
			{
			case XIMasterKeyboard:
				this->add_device(
					keyboards_,
					keyboard_discover_,
					this->create_keyboard(
						param
					)
				);

				return;
			case XIMasterPointer:
				this->add_device(
					mice_,
					mouse_discover_,
					this->create_mouse(
						param
					)
				);

				this->add_device(
					cursors_,
					cursor_discover_,
					this->create_cursor(
						param
					)
				);

				return;
			}
		}
		else if(
			info.flags & XIMasterRemoved
		)
		{
			switch(
				info.use
			)
			{
			case XIMasterKeyboard:
				this->remove_device(
					keyboards_,
					keyboard_remove_,
					device_id
				);

				return;
			case XIMasterPointer:
				this->remove_device(
					mice_,
					mouse_remove_,
					device_id
				);

				this->remove_device(
					cursors_,
					cursor_remove_,
					device_id
				);

				return;
			}
		}
	}
}

template<
	typename Container,
	typename Signal,
	typename DevicePtr
>
void
sge::x11input::processor::add_device(
	Container &_container,
	Signal &_signal,
	DevicePtr const _device
)
{
	_container.push_back(
		_device
	);

	_signal(
		_device
	);
}

template<
	typename Container,
	typename Signal
>
void
sge::x11input::processor::remove_device(
	Container &_container,
	Signal &_signal,
	x11input::device::id const &_id
)
{
	typename Container::iterator const it(
		fcppt::algorithm::find_if_exn(
			_container.begin(),
			_container.end(),
			boost::phoenix::bind(
				&x11input::device::object::id,
				*boost::phoenix::arg_names::arg1
			)
			==
			_id
		)
	);

	typename Container::value_type const ptr(
		*it
	);

	_container.erase(
		it
	);

	_signal(
		ptr
	);
}

void
sge::x11input::processor::on_enter(
	awl::backends::x11::window::event::object const &
)
{
	device_vector const devices_(
		this->devices()
	);

	for(
		device_vector::const_iterator it(
			devices_.begin()
		);
		it != devices_.end();
		++it
	)
		(*it)->on_enter();
}

void
sge::x11input::processor::on_leave(
	awl::backends::x11::window::event::object const &
)
{
	device_vector const devices_(
		this->devices()
	);

	for(
		device_vector::const_iterator it(
			devices_.begin()
		);
		it != devices_.end();
		++it
	)
		(*it)->on_leave();
}
