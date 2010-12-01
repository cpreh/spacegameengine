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


#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/cursor/default.hpp>
#include <sge/gui/cursor/base_ptr.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/grid.hpp>
//#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/global.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/instance.hpp>
#include <sge/all_extensions.hpp>
#include <sge/exception.hpp>

#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::renderer::screen_size const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge gui test")
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						screen_size,
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					sge::renderer::window_mode::windowed,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::manage_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector
			)
		)
		(sge::systems::parameterless::font)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions
			)	
		)
	);

	sge::gui::manager manager(
		sys.renderer(),
		sys.keyboard_collector(),
		sys.mouse_collector(),
		sge::gui::skins::ptr(
			fcppt::make_unique_ptr<
				sge::gui::skins::standard
			>(
				sys.font_system()
			)
		),
		sge::gui::cursor::base_ptr(
			fcppt::make_unique_ptr<
				sge::gui::cursor::default_
			>(
				std::tr1::ref(
					sys.image_loader()
				),
				sys.renderer()
			)
		)
	);

	sge::gui::widgets::backdrop top(
		sge::gui::widgets::parent_data(
			manager
		),
		sge::gui::widgets::parameters()
			.pos(sge::gui::point(10,10))
			.layout(
				fcppt::make_shared_ptr<
					sge::gui::layouts::grid
				>()
			)
			.size(
				sge::gui::dim(400,300)
			)
	);

	fcppt::io::cerr << "added top level widget\n";

	sge::gui::widgets::buttons::text left(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,0)
			),
		SGE_FONT_TEXT_LIT("lefttop me!"));

	sge::gui::widgets::buttons::text right(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(1,0)),
		SGE_FONT_TEXT_LIT("righttop me!"));

	sge::gui::widgets::buttons::text leftbottom(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,3)),
		SGE_FONT_TEXT_LIT("leftbottom me!"));

	fcppt::io::cerr << "added buttons and children\n";

	// set sensible render states
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color =
				sge::image::colors::red())
			(sge::renderer::state::cull_mode::off)
		);

	bool running = true;

	fcppt::signal::scoped_connection const conn(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	fcppt::signal::scoped_connection const conn2(
		left.register_clicked(
			boost::phoenix::ref(running) = false
		)
	);

	fcppt::io::cerr << FCPPT_TEXT("---------------------------\nall widgets added!\n");

	sge::time::timer delete_timer(sge::time::second(static_cast<sge::time::unit>(2)));
	while (running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block block(sys.renderer());

		if (delete_timer.active() && delete_timer.expired())
		{
			fcppt::io::cerr << FCPPT_TEXT("sge: gui test program: removing button\n");
			delete_timer.deactivate();
		}

		manager.update();
		manager.draw();
	}
}
catch (sge::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("caught sge exception: ") << e.string() << FCPPT_TEXT("\n");
}
catch (fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("caught fcppt exception: ") << e.string() << FCPPT_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
