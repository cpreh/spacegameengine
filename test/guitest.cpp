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


#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <iostream>

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>

#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/math/constants.hpp"
#include "../src/renderer/scoped_lock.hpp"
#include "../src/renderer/renderer_system.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/plugin_manager.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/sprite/system.hpp"
#include "../src/texture/no_fragmented_texture.hpp"

#include "../src/gui/color.hpp"
#include "../src/gui/manager.hpp"
#include "../src/gui/button.hpp"

inline sge::pos3 at_pixel(int x, int y) {
	return sge::pos3(
		(x-400) / 400.0,
		-(y-300) / 300.0,
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

	const sge::renderer_system_ptr rs(renderer_plugin->get()());
//	const sge::renderer_caps_array caps(rs->caps());

	const sge::renderer_parameters param(sge::display_mode(800,600,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();
	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	boost::signals::scoped_connection cb(is->register_callback(
		if_(bind(&sge::key_type::code, bind(&sge::key_pair::key, boost::lambda::_1)) == sge::kc::key_escape)
			[var(running)=false])
	);

	sge::key_state_tracker ks(is);



	using sge::gui::manager;
	using sge::gui::canvas;
	using sge::gui::button;
	using sge::gui::color;
	using sge::gui::point;
	using sge::gui::dim2;

	sge::fragmented_texture_ptr mytex(new sge::no_fragmented_texture(rend, sge::point_filter));
	sge::texture_manager texmgr(rend, mytex);

	manager guimgr(dim2(800, 600));

	button b1(&guimgr, sge::colors::green),
	       b2(&guimgr, sge::colors::goldenrod),
	       b3(&guimgr, sge::colors::cornflowerblue);
	b1.resize(dim2(40, 40));
	b2.resize(dim2(50, 30));
	b3.resize(dim2(60, 20));

	b1.move(point( 40, 80));
	b2.move(point( 80,160));
	b3.move(point(160,320));

	sge::index_buffer_ptr ib; {
		const sge::index_buffer::value_type indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		ib = rend->create_index_buffer(6, sge::resource_flags::default_, indices);
	}

	sge::vertex_buffer_ptr vb =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::tex),
		4);
	{
		sge::virtual_texture_ptr canvastex = guimgr.to_texture(texmgr);

		sge::scoped_lock<sge::vertex_buffer_ptr> _lock(vb);
		sge::vertex_buffer::iterator it = vb->begin();

		// top left
		it->pos() = sge::pos3(-1, 1, 0);
		it->tex() = canvastex->translate(0, 0);
		++it;

		// top right
		it->pos() = sge::pos3(1, 1, 0);
		it->tex() = canvastex->translate(1, 0);
		++it;

		// bottom left
		it->pos() = sge::pos3(-1, -1, 0);
		it->tex() = canvastex->translate(0, 1);
		++it;

		// bottom right
		it->pos() = sge::pos3(1, -1, 0);
		it->tex() = canvastex->translate(1, 1);
	}

	sge::vertex_buffer_ptr vb2 =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::diffuse),
		4);
	{
		sge::scoped_lock<sge::vertex_buffer_ptr> _lock(vb2);
		sge::vertex_buffer::iterator it = vb2->begin();

		// top left
		it->pos() = sge::pos3(-1, 1, 0);
		it->diffuse() = sge::colors::blue;
		++it;

		// top right
		it->pos() = sge::pos3(1, 1, 0);
		it->diffuse() = sge::colors::yellow;
		++it;

		// bottom left
		it->pos() = sge::pos3(-1, -1, 0);
		it->diffuse() = sge::colors::red;
		++it;

		// bottom right
		it->pos() = sge::pos3(1, -1, 0);
		it->diffuse() = sge::colors::white;
	}

	rend->set_bool_state(sge::bool_state::enable_alpha_blending, true);

	while(running)
	{
		if(ks[sge::kc::key_return])
			sge::screenshot(rend,pl,"shot.png");

		rend->begin_rendering();
		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();

		rend->set_texture(sge::texture_base_ptr());
		rend->render(vb2, ib, 0, vb2->size(), sge::indexed_primitive_type::triangle, 2, 0);
		rend->set_texture(guimgr.to_texture(texmgr)->my_texture());
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
