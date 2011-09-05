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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/window.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <awl/mainloop/dispatcher.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

int main()
try
{
	awl::mainloop::io_service_shared_ptr const io_service(
		awl::mainloop::asio::create_io_service_base()
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge asio test"),
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
				sge::systems::cursor_option_field::null()
			)
		)
	);

	sys.window().show();

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
	std::exception const &_exception
)
{
	std::cerr
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
