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


#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/quit.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/window/event/destroy_fwd.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/tr1/functional.hpp>


#include <iostream>

sge::systems::modules::window::quit::quit(
	sge::window::system &_system,
	sge::window::object &_window
)
:
	system_(
		_system
	),
	destroy_connection_(
		_window.awl_window_event_processor().destroy_callback(
			std::tr1::bind(
				&sge::systems::modules::window::quit::on_destroy,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sge::systems::modules::window::quit::~quit()
{
}

void
sge::systems::modules::window::quit::on_destroy(
	awl::window::event::destroy const &
)
{
	std::cout << "QUIT\n";

	system_.quit();
}
