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



#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/cursor/default.hpp>
#include <sge/gui/cursor/base_ptr.hpp>

#include <sge/log/activate_levels.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <fcppt/io/cerr.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::log::activate_levels(
		sge::log::global(),
		sge::log::level::debug
	);

	sge::renderer::screen_size const screen_size(640,480);

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			FCPPT_TEXT("sge gui test")))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed,
			sge::renderer::vsync::on,
			sge::renderer::no_multi_sampling
		))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));


	sge::gui::manager m(
		sys.renderer(),
		sys.input_system(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				sys.font_system())),
		sge::gui::cursor::base_ptr(
			new sge::gui::cursor::default_(
				sys.image_loader(),
				sys.renderer())));

	sge::gui::widgets::edit b(
		m,
		sge::gui::widgets::parameters()
			.pos(sge::gui::point(10,10))
			.size(sge::gui::dim(400,300)),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,30));
	//b.text(FCPPT_TEXT("test"));

	// set sensible render states
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color =
				sge::image::colors::black())
			(sge::renderer::state::cull_mode::off)
		);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
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
		sge::renderer::scoped_block const block(sys.renderer());
		m.update();
		m.draw();
	}
}
catch (sge::exception const &e)
{
	sge::cerr << FCPPT_TEXT("caught sge exception: ") << e.string() << SGE_TEXT('\n');
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
