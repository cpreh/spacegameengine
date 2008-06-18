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


#include <cstdlib>
#include <exception>
#include <ostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/font/font.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/types.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/media.hpp>
#include <sge/input/system.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/endianness.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/scoped_connection.hpp>
#include <sge/iostream.hpp>
#include <sge/math/basic_sequence_impl.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/vector_impl.hpp>

template<
	typename,
	sge::math::detail::dim_type>
struct no_policy{};

int main()
try
{
	basic_vector_ext(int, 2)
		   i(1, 2),
	           j(3, 4);	

	bool running = true;
	sge::plugin_manager pm;

	const sge::plugin<sge::renderer::system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer::system>().load();
	const sge::plugin<sge::input::system>::ptr_type input_plugin = pm.get_plugin<sge::input::system>().load();

	const sge::renderer::system_ptr rs(renderer_plugin->get()());
	const sge::renderer::parameters param(sge::renderer::display_mode(1280,1024,sge::renderer::bit_depth::depth32,100), true);
	const sge::renderer::device_ptr rend = rs->create_renderer(param);

	const sge::input::system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::font::system>::ptr_type font_plugin = pm.get_plugin<sge::font::system>().load();
	const sge::font::system_ptr fs(font_plugin->get()());

	const sge::font::metrics_ptr metrics = fs->create_font(sge::media_path() / SGE_TEXT("fonts/default.ttf"), 15);
	const sge::font::drawer_ptr fn_drawer(new sge::font::drawer_3d(rend));

	sge::font::font fn(metrics,fn_drawer);

	using boost::lambda::var;
	using boost::lambda::bind;
//	using boost::lambda::_1;
	using boost::lambda::if_;

	const sge::scoped_connection cb(
		is->register_callback(
			if_(
				bind(
					&sge::input::key_type::code,
					bind(
						&sge::input::key_pair::key,
						boost::lambda::_1))
					== sge::input::kc::key_escape)
				[var(running)=false]));

/*	rend->set_state(
		sge::renderer_state_list
			(sge::bool_state::enable_lighting = true)
			(sge::cull_mode::off)
			(sge::bool_state::clear_zbuffer = true)
			(sge::bool_state::clear_backbuffer = true)
			(sge::cull_mode::front)
			(sge::float_state::zbuffer_clear_val = 0)
			(sge::depth_func::greater)
	);*/

	const sge::string some_text(SGE_TEXT("abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb"));
	while(running)
	{
		rend->begin_rendering();

		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		fn.draw_text(some_text, sge::font::pos(100,100), sge::font::dim(20,500), sge::font::align_h::right, sge::font::align_v::bottom);
		
		rend->end_rendering();
	}
	return EXIT_SUCCESS;
}
catch(const sge::exception& e)
{
	sge::cerr << "Program terminated (sge::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(const std::exception& e)
{
	sge::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	sge::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}
