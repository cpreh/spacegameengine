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


#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/joypad/axis.hpp>
#include <sge/input/joypad/axis_event.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/device_ptr.hpp>
#include <sge/input/joypad/device_vector.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/input/processor.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <awl/mainloop/dispatcher.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

namespace
{

class mouse_listener
{
	FCPPT_NONCOPYABLE(
		mouse_listener
	);
public:
	explicit mouse_listener(
		sge::input::mouse::device_ptr
	);

	~mouse_listener();
private:
	void
	on_button_event(
		sge::input::mouse::button_event const &
	);

	void
	on_axis_event(
		sge::input::mouse::axis_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class cursor_listener
{
	FCPPT_NONCOPYABLE(
		cursor_listener
	);
public:
	explicit cursor_listener(
		sge::input::cursor::object_ptr
	);

	~cursor_listener();
private:
	void
	on_button_event(
		sge::input::cursor::button_event const &
	);

	void
	on_move_event(
		sge::input::cursor::move_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class keyboard_listener
{
	FCPPT_NONCOPYABLE(
		keyboard_listener
	);
public:
	explicit keyboard_listener(
		sge::input::keyboard::device_ptr
	);

	~keyboard_listener();
private:
	void
	on_key_event(
		sge::input::keyboard::key_event const &
	);

	void
	on_key_repeat_event(
		sge::input::keyboard::key_repeat_event const &
	);

	void
	on_char_event(
		sge::input::keyboard::char_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class joypad_listener
{
	FCPPT_NONCOPYABLE(
		joypad_listener
	);
public:
	explicit joypad_listener(
		sge::input::joypad::device_ptr
	);

	~joypad_listener();
private:
	void
	on_button_event(
		sge::input::joypad::button_event const &
	);

	void
	on_axis_event(
		sge::input::joypad::axis_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class device_manager
{
	FCPPT_NONCOPYABLE(
		device_manager
	);
public:
	explicit device_manager(
		sge::input::processor &
	);

	~device_manager();
private:
	void
	on_mouse_add(
		sge::input::mouse::device_ptr
	);

	void
	on_mouse_remove(
		sge::input::mouse::device_ptr
	);

	void
	on_cursor_add(
		sge::input::cursor::object_ptr
	);

	void
	on_cursor_remove(
		sge::input::cursor::object_ptr
	);

	void
	on_keyboard_add(
		sge::input::keyboard::device_ptr
	);

	void
	on_keyboard_remove(
		sge::input::keyboard::device_ptr
	);

	void
	on_joypad_add(
		sge::input::joypad::device_ptr
	);

	void
	on_joypad_remove(
		sge::input::joypad::device_ptr
	);

	typedef boost::ptr_map<
		sge::input::mouse::device_ptr,
		mouse_listener
	> mouse_listener_map;

	typedef boost::ptr_map<
		sge::input::cursor::object_ptr,
		cursor_listener
	> cursor_listener_map;

	typedef boost::ptr_map<
		sge::input::keyboard::device_ptr,
		keyboard_listener
	> keyboard_listener_map;

	typedef boost::ptr_map<
		sge::input::joypad::device_ptr,
		joypad_listener
	> joypad_listener_map;

	fcppt::signal::connection_manager const connections_;

	mouse_listener_map mouse_listeners_;

	cursor_listener_map cursor_listeners_;

	keyboard_listener_map keyboard_listeners_;

	joypad_listener_map joypad_listeners_;
};

}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	awl::mainloop::io_service_shared_ptr const io_service(
		awl::mainloop::asio::create_io_service_base()
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge input example"),
					sge::window::dim(
						1024,
						768
					)
				)
			)
			.io_service(
				io_service
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
	);

	sys.window().show();

	::device_manager const manager(
		sys.input_processor()
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				std::tr1::bind(
					&awl::mainloop::dispatcher::stop,
					sys.window().awl_dispatcher()
				)
			)
		)
	);

	io_service->run();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
mouse_listener::mouse_listener(
	sge::input::mouse::device_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_device->button_callback(
					std::tr1::bind(
						&mouse_listener::on_button_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->axis_callback(
					std::tr1::bind(
						&mouse_listener::on_axis_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

mouse_listener::~mouse_listener()
{
}

void
mouse_listener::on_button_event(
	sge::input::mouse::button_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("mouse_button_event: ")
		<< _event.button_code()
		<< FCPPT_TEXT(' ')
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
mouse_listener::on_axis_event(
	sge::input::mouse::axis_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("mouse_axis_event: ")
		<< _event.axis()
		<< FCPPT_TEXT(' ')
		<< _event.axis_value()
		<< FCPPT_TEXT('\n');
}


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
cursor_listener::cursor_listener(
	sge::input::cursor::object_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_device->button_callback(
					std::tr1::bind(
						&cursor_listener::on_button_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->move_callback(
					std::tr1::bind(
						&cursor_listener::on_move_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

cursor_listener::~cursor_listener()
{
}

void
cursor_listener::on_button_event(
	sge::input::cursor::button_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("cursor_button_event: ")
		<< _event.button_code()
		<< FCPPT_TEXT(' ')
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
cursor_listener::on_move_event(
	sge::input::cursor::move_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("cursor_move_event: ")
		<< _event.position()
		<< FCPPT_TEXT('\n');
}


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
keyboard_listener::keyboard_listener(
	sge::input::keyboard::device_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_device->key_callback(
					std::tr1::bind(
						&keyboard_listener::on_key_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->key_repeat_callback(
					std::tr1::bind(
						&keyboard_listener::on_key_repeat_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->char_callback(
					std::tr1::bind(
						&keyboard_listener::on_char_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

keyboard_listener::~keyboard_listener()
{
}

void
keyboard_listener::on_key_event(
	sge::input::keyboard::key_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("key_event: ")
		<< _event.key_code()
		<< FCPPT_TEXT(' ')
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
keyboard_listener::on_key_repeat_event(
	sge::input::keyboard::key_repeat_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("key_repeat_event: ")
		<< _event.key_code()
		<< FCPPT_TEXT('\n');
}

void
keyboard_listener::on_char_event(
	sge::input::keyboard::char_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("char_event: ")
		<< _event.character()
		<< FCPPT_TEXT(' ')
		<< _event.repeated()
		<< FCPPT_TEXT('\n');
}


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
joypad_listener::joypad_listener(
	sge::input::joypad::device_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_device->button_callback(
					std::tr1::bind(
						&joypad_listener::on_button_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->axis_callback(
					std::tr1::bind(
						&joypad_listener::on_axis_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

joypad_listener::~joypad_listener()
{
}

void
joypad_listener::on_button_event(
	sge::input::joypad::button_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("joypad_button_event: ")
		<< _event.button_id()
		<< FCPPT_TEXT(' ')
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
joypad_listener::on_axis_event(
	sge::input::joypad::axis_event const &_event
)
{
	fcppt::io::cout
		<< FCPPT_TEXT("joypad_axis_event: ")
		<< _event.axis().id()
		<< FCPPT_TEXT(' ')
		<< _event.axis_value()
		<< FCPPT_TEXT('\n');
}


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
device_manager::device_manager(
	sge::input::processor &_processor
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor.mouse_discover_callback(
					std::tr1::bind(
						&device_manager::on_mouse_add,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.mouse_remove_callback(
					std::tr1::bind(
						&device_manager::on_mouse_remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.cursor_discover_callback(
					std::tr1::bind(
						&device_manager::on_cursor_add,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.cursor_remove_callback(
					std::tr1::bind(
						&device_manager::on_cursor_remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.keyboard_discover_callback(
					std::tr1::bind(
						&device_manager::on_keyboard_add,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.keyboard_remove_callback(
					std::tr1::bind(
						&device_manager::on_keyboard_remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.joypad_discover_callback(
					std::tr1::bind(
						&device_manager::on_joypad_add,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.joypad_remove_callback(
					std::tr1::bind(
						&device_manager::on_joypad_remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	mouse_listeners_(),
	cursor_listeners_(),
	keyboard_listeners_(),
	joypad_listeners_()
{
	{
		sge::input::mouse::device_vector const devices(
			_processor.mice()
		);

		for(
			sge::input::mouse::device_vector::const_iterator it(
				devices.begin()
			);
			it != devices.end();
			++it
		)
			this->on_mouse_add(
				*it
			);
	}

	{
		sge::input::cursor::object_vector const objects(
			_processor.cursors()
		);

		for(
			sge::input::cursor::object_vector::const_iterator it(
				objects.begin()
			);
			it != objects.end();
			++it
		)
			this->on_cursor_add(
				*it
			);
	}

	{
		sge::input::keyboard::device_vector const devices(
			_processor.keyboards()
		);

		for(
			sge::input::keyboard::device_vector::const_iterator it(
				devices.begin()
			);
			it != devices.end();
			++it
		)
			this->on_keyboard_add(
				*it
			);
	}

	{
		sge::input::joypad::device_vector const devices(
			_processor.joypads()
		);

		for(
			sge::input::joypad::device_vector::const_iterator it(
				devices.begin()
			);
			it != devices.end();
			++it
		)
			this->on_joypad_add(
				*it
			);
	}
}
FCPPT_PP_POP_WARNING

device_manager::~device_manager()
{
}

void
device_manager::on_mouse_add(
	sge::input::mouse::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			mouse_listeners_,
			_device,
			fcppt::make_unique_ptr<
				mouse_listener
			>(
				_device
			)
		).second
		== true
	);

	fcppt::io::cout
		<< FCPPT_TEXT("mouse_add: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_mouse_remove(
	sge::input::mouse::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		mouse_listeners_.erase(
			_device
		) == 1u
	);

	fcppt::io::cout
		<< FCPPT_TEXT("mouse_remove: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_cursor_add(
	sge::input::cursor::object_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			cursor_listeners_,
			_device,
			fcppt::make_unique_ptr<
				cursor_listener
			>(
				_device
			)
		).second
		== true
	);

	fcppt::io::cout
		<< FCPPT_TEXT("cursor_add: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_cursor_remove(
	sge::input::cursor::object_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		cursor_listeners_.erase(
			_device
		) == 1u
	);

	fcppt::io::cout
		<< FCPPT_TEXT("cursor_remove: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_keyboard_add(
	sge::input::keyboard::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			keyboard_listeners_,
			_device,
			fcppt::make_unique_ptr<
				keyboard_listener
			>(
				_device
			)
		).second
		== true
	);

	fcppt::io::cout
		<< FCPPT_TEXT("keyboard_add: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_keyboard_remove(
	sge::input::keyboard::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		keyboard_listeners_.erase(
			_device
		) == 1u
	);

	fcppt::io::cout
		<< FCPPT_TEXT("keyboard_remove: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_joypad_add(
	sge::input::joypad::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			joypad_listeners_,
			_device,
			fcppt::make_unique_ptr<
				joypad_listener
			>(
				_device
			)
		).second
		== true
	);

	fcppt::io::cout
		<< FCPPT_TEXT("joypad_add: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

void
device_manager::on_joypad_remove(
	sge::input::joypad::device_ptr const _device
)
{
	FCPPT_ASSERT_ERROR(
		joypad_listeners_.erase(
			_device
		) == 1u
	);

	fcppt::io::cout
		<< FCPPT_TEXT("joypad_remove: ")
		<< _device
		<< FCPPT_TEXT('\n');
}

}
