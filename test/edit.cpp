/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/logger.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size_t const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge gui test")))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));

	
	sge::gui::manager m(
		sys.renderer(),
		sys.image_loader(),
		sys.input_system(),
		sys.font_system(),
		sge::make_shared_ptr<
			sge::gui::skins::standard
		>());
	
	sge::gui::widgets::edit b(
		(sge::gui::widget::parent_data(m)),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,30));
	b.pos(sge::gui::point(10,10));
	b.size(sge::gui::dim(400,300));
	//b.text(SGE_TEXT("test"));

	// set sensible render states
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color =
				sge::renderer::colors::black())
			(sge::renderer::state::cull_mode::off)
		);
	
	bool running = true;

	sge::signals::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());
		m.draw();
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
	return EXIT_FAILURE;
}
