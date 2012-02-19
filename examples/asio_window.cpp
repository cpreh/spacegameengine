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


#include <example_main.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/io_service_scoped_ptr.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	awl::mainloop::io_service_scoped_ptr const io_service(
		awl::mainloop::asio::create_io_service_base()
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge asio test")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
			.io_service(
				*io_service
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

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	io_service->run();

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< '\n';

	return awl::main::exit_failure();
}
