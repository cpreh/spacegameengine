/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <iostream>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>

#include "../src/plugin_manager.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/renderer/lock_ptr.hpp"
#include "../src/renderer/renderer_system.hpp"
#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"

#include "../src/gui/pixmap.hpp"

inline sge::pos3 at_pixel(int x, int y) {
	return sge::pos3(
		(x-512) / 512.0,
		(y-384) / 384.0,
		0
	);
}

int main()
try
{
	std::srand(std::time(0));
	bool running = true;
	sge::plugin_manager pm;

	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());
	const sge::renderer_caps_array caps(rs->caps());

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	boost::signals::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::first,boost::lambda::_1)) == sge::KC_ESC)[var(running)=false]));

	sge::key_state_tracker ks(is);

	sge::index_buffer_ptr ib;
	sge::vertex_buffer_ptr vb =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::tex),
		4);
	{
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(vb);
		sge::vertex_buffer::iterator it = vb->begin();

		// top left
		it->pos() = at_pixel(600, 200);
		++it;

		// top right
		it->pos() = at_pixel(900, 200);
		++it;

		// bottom left
		it->pos() = at_pixel(600, 400);
		++it;

		// bottom right
		it->pos() = at_pixel(900, 400);
	}

	{
		const sge::index_buffer::value_type indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		ib = rend->create_index_buffer(6, sge::resource_flags::default_, indices);
	}

	sge::gui::pixmap pixmap(sge::gui::dim2(300, 200));

	using sge::gui::color;
	pixmap.fill(sge::colors::mintcream);

//	sge::texture_ptr pixmaptex(pixmap.to_texture(rend));

	while(running)
	{
		rend->begin_rendering();
		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();

//		rend->set_texture(pixmaptex);
		rend->render(vb, ib, 0, vb->size(), sge::indexed_primitive_type::triangle, 2, 0);

		rend->end_rendering();
	}
	return EXIT_SUCCESS;
}
catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}
