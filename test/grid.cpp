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

#include <sge/gui/manager.hpp>
#include <sge/gui/cursor/default.hpp>
#include <sge/gui/cursor/base_ptr.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/layouts/grid.hpp>
//#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/headers.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/font/system.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

namespace
{
struct end_program
{
	end_program(bool &running) : running(running) {}
	void operator()() const { running = false; }
	bool &running;
};

class input_functor
{
	public:
	explicit input_functor(bool &running)
		: running(running)
	{
	}

	void operator()(sge::input::key_pair const &k) const
	{
		if (k.key().code() == sge::input::kc::key_escape)
			running = false;
	}
	private:
	bool &running;
};
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge gui test")
		))
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
		sys.input_system(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				sys.font_system())),
		sge::gui::cursor::base_ptr(
			new sge::gui::cursor::default_(
				sys.image_loader(),
				sys.renderer())));
	
	sge::gui::widgets::backdrop top(
		sge::gui::widgets::parent_data(m),
		sge::gui::widgets::parameters()
			.pos(sge::gui::point(10,10))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::grid>())
			.size(
				sge::gui::dim(400,300)));

	sge::cerr << "added top level widget\n";

	sge::gui::widgets::buttons::text left(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,0)),
		SGE_TEXT("lefttop me!"));
	
	sge::gui::widgets::buttons::text right(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(1,0)),
		SGE_TEXT("righttop me!"));

	sge::gui::widgets::buttons::text leftbottom(
		top,
		sge::gui::widgets::parameters()
			.pos(
				sge::gui::point(0,3)),
		SGE_TEXT("leftbottom me!"));

	sge::cerr << "added buttons and children\n";

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
	end_program p(running);
	sge::signal::scoped_connection const conn(
		sys.input_system()->register_callback(
			input_functor(
				running
			)
		)
	);
	
	sge::signal::scoped_connection const conn2(
		left.register_clicked(p)
	);
	sge::cerr << SGE_TEXT("---------------------------\nall widgets added!\n");
	
	sge::time::timer delete_timer(sge::time::second(static_cast<sge::time::unit>(2)));
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());

		if (delete_timer.active() && delete_timer.expired())
		{
			sge::cerr << SGE_TEXT("sge: gui test program: removing button\n");
			delete_timer.deactivate();
		}

		m.update();
		m.draw();
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
