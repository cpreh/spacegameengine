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
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/window/instance.hpp>
#include <sge/log/global.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

namespace
{

void mod_callback(
	sge::input::keyboard::key_event const &kp,
	sge::input::modifier::states const &mods)
{
	if (mods[sge::input::keyboard::key_code::lshift])
		fcppt::io::cerr << FCPPT_TEXT("S-");

	if (mods[sge::input::keyboard::key_code::lctrl])
		fcppt::io::cerr << FCPPT_TEXT("C-");

	if (mods[sge::input::keyboard::key_code::alt])
		fcppt::io::cerr << FCPPT_TEXT("A-");

	fcppt::io::cerr << kp.key().character() << FCPPT_TEXT('\n');
}

}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge modifier test"),
					sge::window::dim_type(
						1024,
						768)
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
			)
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::input::modifier::filter mf(
		*sys.keyboard_collector()
	);

	fcppt::signal::scoped_connection const pc(
		mf.register_callback(&mod_callback));

	sys.window()->show();

	while(running)
	{
		sys.window()->dispatch();
	}
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
