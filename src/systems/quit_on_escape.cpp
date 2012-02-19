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


#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


fcppt::signal::auto_connection
sge::systems::quit_on_escape(
	sge::systems::instance const &_instance
)
{
	return
		_instance.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				std::tr1::bind(
					&sge::window::system::quit,
					&_instance.window_system(),
					awl::main::exit_success()
				)
			)
		);
}
