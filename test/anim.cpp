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
#include <sge/iostream.hpp>
#include <sge/media.hpp>
#include <sge/window.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/util.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/time/second.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/assign/list_of.hpp>
#include <cstdlib>
#include <exception>
#include <ostream>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image));
	
	const sge::input::system_ptr    is   = sys.input_system();
	const sge::renderer::device_ptr rend = sys.renderer();
	const sge::image::loader_ptr    pl   = sys.image_loader();

	const sge::image::object_ptr img1(pl->load(sge::media_path() / SGE_TEXT("cloudsquare.jpg"))),
	                             img2(pl->load(sge::media_path() / SGE_TEXT("grass.png")));

	const sge::texture::default_creator<sge::texture::no_fragmented> creator(rend, sge::renderer::linear_filter);
	sge::texture::manager tex_man(rend, creator);

	const sge::texture::part_ptr tex1(sge::texture::add(tex_man, img1)),
	                             tex2(sge::texture::add(tex_man, img2));

	sge::sprite::system ss(rend);
	sge::sprite::object spr(
		sge::sprite::point(0,0),
		sge::texture::part_ptr(),
		sge::sprite::dim(
			rend->screen_size().w(),
			static_cast<sge::sprite::unit>(
				rend->screen_size().h())),
		boost::none,
		boost::none,
		boost::none,
		boost::none);

	const sge::sprite::animation_series::entity_vector series = 
		boost::assign::list_of
			(sge::sprite::animation_entity(sge::time::second(sge::su(0.5)), tex1))
			(sge::sprite::animation_entity(sge::time::second(sge::su(1)), tex2));
	sge::sprite::texture_animation anim(
		series,
		sge::sprite::texture_animation::loop_method::repeat,
		spr);

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	bool running = true;

	sge::signals::scoped_connection const cb(
		is->register_callback(
			if_(bind(&sge::input::key_type::code,
				bind(&sge::input::key_pair::key,boost::lambda::_1))
			== sge::input::kc::key_escape)
		[var(running)=false])
	);

	rend->set_state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
	);
	rend->projection(sge::math::matrix_orthogonal_xy());

	while(running)
	{
		sge::renderer::scoped_block const block_(rend);
		sge::window::dispatch();
		is->dispatch();
		anim.process();
		ss.render(spr);
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
