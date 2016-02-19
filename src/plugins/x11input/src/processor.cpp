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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/x11input/create_parameters.hpp>
#include <sge/x11input/input_context.hpp>
#include <sge/x11input/input_method.hpp>
#include <sge/x11input/logger.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/send_init_event.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/object_unique_ptr.hpp>
#include <sge/x11input/device/hierarchy_demuxer.hpp>
#include <sge/x11input/device/hierarchy_event.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <sge/x11input/device/manager/create_function.hpp>
#include <sge/x11input/device/manager/make_config.hpp>
#include <sge/x11input/focus/object.hpp>
#include <sge/x11input/focus/object_unique_ptr.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/device_unique_ptr.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/mouse/device_unique_ptr.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/intern_atom.hpp>
#include <awl/backends/x11/cursor/create_invisible.hpp>
#include <awl/backends/x11/cursor/object.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/callback.hpp>
#include <awl/backends/x11/window/event/object.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <awl/backends/x11/window/event/type.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::processor::processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system,
	awl::backends::x11::system::event::opcode const _opcode
)
:
	opcode_(
		_opcode
	),
	x11_window_(
		fcppt::cast::static_downcast<
			awl::backends::x11::window::object const &
		>(
			_window.awl_object()
		)
	),
	window_event_processor_(
		fcppt::cast::static_downcast<
			awl::backends::x11::window::event::processor &
		>(
			_window.awl_window_event_processor()
		)
	),
	system_event_processor_(
		fcppt::cast::static_downcast<
			awl::backends::x11::system::event::processor &
		>(
			_window_system.awl_system_event_processor()
		)
	),
	window_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		sge::x11input::device::demuxer_enabled(
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
		sge::x11input::device::demuxer_enabled(
			false
		)
	),
	hierarchy_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		sge::x11input::device::demuxer_enabled(
			true
		)
	),
	enter_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		sge::x11input::device::demuxer_enabled(
			true
		)
	),
	leave_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_,
		sge::x11input::device::demuxer_enabled(
			true
		)
	),
	invisible_cursor_(
		awl::backends::x11::cursor::create_invisible(
			x11_window_.display()
		)
	),
	input_method_(
		fcppt::make_unique_ptr<
			sge::x11input::input_method
		>(
			x11_window_.display(),
			x11_window_.class_hint()
		)
	),
	input_context_(
		fcppt::make_unique_ptr<
			x11input::input_context
		>(
			input_method_->get(),
			input_method_->class_hint(),
			x11_window_
		)
	),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	focus_discover_(),
	focus_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	device_manager_(
		x11_window_.display(),
		fcppt::assign::make_container<
			sge::x11input::device::manager::config_map
		>(
			std::make_pair(
				sge::x11input::device::use(
					XIMasterKeyboard
				),
				sge::x11input::device::manager::make_config<
					sge::x11input::focus::object
				>(
					focus_discover_,
					focus_remove_,
					sge::x11input::device::manager::create_function<
						sge::x11input::focus::object
					>{
						std::bind(
							&sge::x11input::processor::create_focus,
							this,
							std::placeholders::_1
						)
					}
				)
			)
		)
		(
			std::make_pair(
				sge::x11input::device::use(
					XISlaveKeyboard
				),
				sge::x11input::device::manager::make_config<
					sge::x11input::keyboard::device
				>(
					keyboard_discover_,
					keyboard_remove_,
					sge::x11input::device::manager::create_function<
						sge::x11input::keyboard::device
					>{
						std::bind(
							&sge::x11input::processor::create_keyboard,
							this,
							std::placeholders::_1
						)
					}
				)
			)
		)
		(
			std::make_pair(
				sge::x11input::device::use(
					XIMasterPointer
				),
				sge::x11input::device::manager::make_config<
					sge::x11input::cursor::object
				>(
					cursor_discover_,
					cursor_remove_,
					sge::x11input::device::manager::create_function<
						sge::x11input::cursor::object
					>{
						std::bind(
							&sge::x11input::processor::create_cursor,
							this,
							std::placeholders::_1
						)
					}
				)
			)
		)
		(
			std::make_pair(
				sge::x11input::device::use(
					XISlavePointer
				),
				sge::x11input::device::manager::make_config<
					sge::x11input::mouse::device
				>(
					mouse_discover_,
					mouse_remove_,
					sge::x11input::device::manager::create_function<
						sge::x11input::mouse::device
					>{
						std::bind(
							&sge::x11input::processor::create_mouse,
							this,
							std::placeholders::_1
						)
					}
				)
			)
		)
		.move_container()
	),
	cursor_manager_(),
	init_atom_(
		awl::backends::x11::intern_atom(
			x11_window_.display(),
			"SGE start atom"
		)
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			hierarchy_demuxer_.register_callback(
				awl::backends::x11::system::event::type(
					XI_HierarchyChanged
				),
				sge::x11input::device::id(
					XIAllDevices
				),
				sge::x11input::device::hierarchy_demuxer::callback{
					std::bind(
						&sge::x11input::processor::on_hierarchy_changed,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			window_event_processor_.register_callback(
				awl::backends::x11::window::event::type(
					FocusIn
				),
				awl::backends::x11::window::event::callback{
					std::bind(
						&sge::x11input::processor::on_focus_in,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			window_event_processor_.register_callback(
				awl::backends::x11::window::event::type(
					FocusOut
				),
				awl::backends::x11::window::event::callback{
					std::bind(
						&sge::x11input::processor::on_focus_out,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			window_event_processor_.register_callback(
				awl::backends::x11::window::event::type(
					ClientMessage
				),
				awl::backends::x11::window::event::callback{
					std::bind(
						&sge::x11input::processor::on_client_message,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			cursor_discover_.connect(
				sge::input::cursor::discover_callback{
					std::bind(
						&sge::x11input::cursor::manager::discover,
						&cursor_manager_,
						std::placeholders::_1
					)
				}
			)
		)
		(
			cursor_remove_.connect(
				sge::input::cursor::remove_callback{
					std::bind(
						&sge::x11input::cursor::manager::remove,
						&cursor_manager_,
						std::placeholders::_1
					)
				}
			)
		)
		.move_container()
	)
{
	sge::x11input::device::info::multi const current_devices(
		x11_window_.display()
	);

	for(
		int const index
		:
		fcppt::make_int_range_count(
			current_devices.size()
		)
	)
		device_manager_.initial(
			current_devices[
				index
			]
		);

	sge::x11input::send_init_event(
		x11_window_,
		init_atom_
	);
}

sge::x11input::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::keyboard_discover_callback(
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
sge::x11input::processor::keyboard_remove_callback(
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
sge::x11input::processor::mouse_discover_callback(
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
sge::x11input::processor::mouse_remove_callback(
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
sge::x11input::processor::focus_discover_callback(
	sge::input::focus::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::focus_remove_callback(
	sge::input::focus::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::x11input::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

sge::x11input::device::parameters
sge::x11input::processor::device_parameters(
	sge::x11input::create_parameters const &_param
)
{
	return
		sge::x11input::device::parameters(
			_param,
			opcode_,
			x11_window_,
			window_demuxer_,
			raw_demuxer_,
			enter_demuxer_,
			leave_demuxer_
		);
}

sge::x11input::keyboard::device_unique_ptr
sge::x11input::processor::create_keyboard(
	sge::x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			sge::x11input::keyboard::device
		>(
			this->device_parameters(
				_param
			)
		);
}

sge::x11input::mouse::device_unique_ptr
sge::x11input::processor::create_mouse(
	sge::x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			sge::x11input::mouse::device
		>(
			this->device_parameters(
				_param
			)
		);
}

sge::x11input::focus::object_unique_ptr
sge::x11input::processor::create_focus(
	sge::x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			sge::x11input::focus::object
		>(
			this->device_parameters(
				_param
			),
			*input_context_
		);
}

sge::x11input::cursor::object_unique_ptr
sge::x11input::processor::create_cursor(
	sge::x11input::create_parameters const &_param
)
{
	return
		fcppt::make_unique_ptr<
			sge::x11input::cursor::object
		>(
			this->device_parameters(
				_param
			),
			*invisible_cursor_,
			cursor_manager_.entered()
		);
}

void
sge::x11input::processor::on_hierarchy_changed(
	sge::x11input::device::hierarchy_event const &_event
)
{
	for(
		int const index
		:
		fcppt::make_int_range_count(
			_event.get().num_info
		)
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
		sge::x11input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("FocusIn")
	);

	raw_demuxer_.active(
		true
	);

	// FIXME: We need to manage the cursors that belong to this focus
	cursor_manager_.focus_in();
}

void
sge::x11input::processor::on_focus_out(
	awl::backends::x11::window::event::object const &
)
{
	FCPPT_LOG_DEBUG(
		sge::x11input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("FocusOut")
	);

	raw_demuxer_.active(
		false
	);

	// FIXME: We need to manage the cursors that belong to this focus
	cursor_manager_.focus_out();
}

void
sge::x11input::processor::on_client_message(
	awl::backends::x11::window::event::object const &_object
)
{
	FCPPT_LOG_DEBUG(
		sge::x11input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("ClientMessage")
	);

	if(
		_object.get().xclient.message_type
		!=
		init_atom_.get()
	)
		return;

	device_manager_.dispatch_initial();
}
