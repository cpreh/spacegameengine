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


#include <sge/input/info/optional_string.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/device_ptr.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/manager.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/manager.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <awl/mainloop/dispatcher.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::string const
output_optional_string(
	sge::input::info::optional_string const &
);

void
joypad_discover(
	sge::input::joypad::discover_event const &
);

void
joypad_remove(
	sge::input::joypad::remove_event const &
);

void
joypad_absolute_axis(
	sge::input::joypad::device_ptr,
	sge::input::joypad::absolute_axis_event const &
);

void
joypad_button(
	sge::input::joypad::device_ptr,
	sge::input::joypad::button_event const &
);

void
joypad_relative_axis(
	sge::input::joypad::device_ptr,
	sge::input::joypad::relative_axis_event const &
);

void
mouse_discover(
	sge::input::mouse::discover_event const &
);

void
mouse_remove(
	sge::input::mouse::remove_event const &
);

void
mouse_axis(
	sge::input::mouse::device_ptr,
	sge::input::mouse::axis_event const &
);

void
mouse_button(
	sge::input::mouse::device_ptr,
	sge::input::mouse::button_event const &
);

}

int
main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	awl::mainloop::io_service_shared_ptr const io_service(
		awl::mainloop::asio::create_io_service_base()
	);

	sge::systems::instance const sys(
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

	fcppt::io::cout()
		<< std::boolalpha;

	sge::input::joypad::manager const joypad_manager(
		sys.input_processor(),
		sge::input::joypad::discover_callback(
			::joypad_discover
		),
		sge::input::joypad::remove_callback(
			::joypad_remove
		),
		sge::input::joypad::manager::absolute_axis_callback(
			::joypad_absolute_axis
		),
		sge::input::joypad::manager::button_callback(
			::joypad_button
		),
		sge::input::joypad::manager::relative_axis_callback(
			::joypad_relative_axis
		)
	);

	sge::input::mouse::manager const mouse_manager(
		sys.input_processor(),
		sge::input::mouse::discover_callback(
			::mouse_discover
		),
		sge::input::mouse::remove_callback(
			::mouse_remove
		),
		sge::input::mouse::manager::axis_callback(
			::mouse_axis
		),
		sge::input::mouse::manager::button_callback(
			::mouse_button
		)
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
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}

namespace
{

fcppt::string const
output_optional_string(
	sge::input::info::optional_string const &_name
)
{
	return
		_name
		?
			*_name
		:
			fcppt::string(
				FCPPT_TEXT("unnamed")
			)
		;
}

void
joypad_discover(
	sge::input::joypad::discover_event const &_event
)
{
	sge::input::joypad::info const info(
		_event.device()->info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_discover: ")
		<< _event.device()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT('\n');

	{
		sge::input::joypad::absolute_axis_info_container::vector const &absolute_axis(
			info.absolute_axis().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("absolute axis: ")
			<< absolute_axis.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::absolute_axis_info_container::vector::const_iterator it(
				absolute_axis.begin()
			);
			it != absolute_axis.end();
			++it
		)
		{
			sge::input::joypad::absolute_axis_info const &axis_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("name: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT("\n\tmin: ")
				<< axis_info.min()
				<< FCPPT_TEXT("\n\tmax: ")
				<< axis_info.max()
				<< FCPPT_TEXT('\n');
		}
	}

	{
		sge::input::joypad::relative_axis_info_container::vector const &relative_axis(
			info.relative_axis().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("relative axis: ")
			<< relative_axis.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::relative_axis_info_container::vector::const_iterator it(
				relative_axis.begin()
			);
			it != relative_axis.end();
			++it
		)
		{
			sge::input::joypad::relative_axis_info const &axis_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("name: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT('\n');
		}
	}

	{
		sge::input::joypad::button_info_container::vector const &buttons(
			info.buttons().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("buttons: ")
			<< buttons.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::button_info_container::vector::const_iterator it(
				buttons.begin()
			);
			it != buttons.end();
			++it
		)
		{
			sge::input::joypad::button_info const &button_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("name: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT('\n');
		}
	}

}

void
joypad_remove(
	sge::input::joypad::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_discover: ")
		<< _event.device()
		<< FCPPT_TEXT('\n');
}

void
joypad_absolute_axis(
	sge::input::joypad::device_ptr const _device,
	sge::input::joypad::absolute_axis_event const &_event
)
{
}

void
joypad_button(
	sge::input::joypad::device_ptr const _device,
	sge::input::joypad::button_event const &_event
)
{
}

void
joypad_relative_axis(
	sge::input::joypad::device_ptr const _device,
	sge::input::joypad::relative_axis_event const &_event
)
{
}

void
mouse_discover(
	sge::input::mouse::discover_event const &_event
)
{
	sge::input::mouse::info const info(
		_event.device()->info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_discover: ")
		<< _event.device()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT('\n');
}

void
mouse_remove(
	sge::input::mouse::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_discover: ")
		<< _event.device()
		<< FCPPT_TEXT('\n');
}

void
mouse_axis(
	sge::input::mouse::device_ptr const _device,
	sge::input::mouse::axis_event const &_event
)
{
}

void
mouse_button(
	sge::input::mouse::device_ptr const _device,
	sge::input::mouse::button_event const &_event
)
{
}

}
