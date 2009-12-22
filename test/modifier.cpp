/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/classification.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/input/action.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
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
	sge::input::key_pair const &kp,
	sge::input::modifier::states const &mods)
{
	if (mods[sge::input::kc::key_lshift])
		fcppt::io::cerr << FCPPT_TEXT("S-");

	if (mods[sge::input::kc::key_lctrl])
		fcppt::io::cerr << FCPPT_TEXT("C-");

	if (mods[sge::input::kc::key_alt])
		fcppt::io::cerr << FCPPT_TEXT("A-");

	fcppt::io::cerr << kp.key().char_code() << FCPPT_TEXT('\n');
}

}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::renderer::screen_size const screen_size(1024,768);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			FCPPT_TEXT("sge modifier test")
		))
		/*
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))*/
		(sge::systems::parameterless::input));

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::input::modifier::filter mf(sys.input_system());

	fcppt::signal::scoped_connection const pc(
		mf.register_callback(&mod_callback));

	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
