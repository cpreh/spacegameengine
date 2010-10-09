/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/systems/parameterless.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/dim_type.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/mainloop/io_service.hpp>
#include <sge/mainloop/asio/create_io_service.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

int main()
try
{
	sge::mainloop::io_service_ptr const io_service(
		sge::mainloop::asio::create_io_service()
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge asio test")
			)
			.dim(
				sge::window::dim_type(
					1024,
					768
				)
			)
			.io_service(
				io_service
			)
		)
		(
			sge::systems::parameterless::input
		)
	);

	sys.window()->show();

	fcppt::signal::scoped_connection const input_connection(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				std::tr1::bind(
					&sge::mainloop::io_service::stop,
					io_service
				)
			)
		)
	);

	io_service->run();
}
SGE_MAINLOOP_CATCH_BLOCK
