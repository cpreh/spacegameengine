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

#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/image/loader.hpp>
#include <sge/window/parameters.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/console/object.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/stdlib.hpp>
#include <sge/font/system.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <ostream>
#include <cstdlib>

namespace
{

void fallback(
	sge::string const &arg)
{
	sge::cout << SGE_TEXT("fallback called with argument:") << arg << SGE_TEXT("\n");
}

void quit(bool &running,sge::console::arg_list const &)
{
	running = false;
}

}

int main()
try
{
	bool running = true;

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge console test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));

	sge::console::object o(SGE_TEXT('/'));
	
	sge::signals::connection const c0 = o.insert(
		SGE_TEXT("quit"),
		boost::bind(&quit,boost::ref(running),_1),
		SGE_TEXT("quit test"));

	sge::signals::connection const c1 = o.register_fallback(
		&fallback);

	sge::image::object_ptr const 
		image_bg(
			sys.image_loader()->load(
				sge::media_path()/SGE_TEXT("grass.png")));

	sge::texture::default_creator<sge::texture::no_fragmented> const 
		creator(
			sys.renderer(),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter);

	sge::texture::manager tex_man(sys.renderer(),creator);

	sge::texture::const_part_ptr const 
		tex_bg(
			sge::texture::add_image(
				tex_man, 
				image_bg));

	sge::console::gfx gfx_(
		o,
		sys.renderer(),
		sge::renderer::rgba8_color(255,255,255,255),
		sys.font_system()->create_font(
			sge::media_path()/SGE_TEXT("fonts")/SGE_TEXT("default.ttf"),
			15),
		sys.input_system(),
		sge::sprite::object(
			sge::sprite::point(0,0),
			tex_bg,
			sge::sprite::dim(400,300)));

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::rgba8_color(0, 0, 0, 0))
	);

	sge::console::stdlib lib(
		o,
		boost::bind(&sge::console::gfx::print,&gfx_,_1),
		boost::bind(&sge::console::gfx::print,&gfx_,_1));

	gfx_.active(true);
	
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());
		gfx_.draw();
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
