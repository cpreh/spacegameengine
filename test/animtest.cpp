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
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/assign/list_of.hpp>
#include "../src/systems.hpp"
#include "../src/iostream.hpp"
#include "../src/ostream.hpp"
#include "../src/media.hpp"
#include "../src/init.hpp"
#include "../src/math/matrix_impl.hpp"
#include "../src/scoped_connection.hpp"
#include "../src/renderer/renderer.hpp"
#include "../src/renderer/scoped_renderblock.hpp"
#include "../src/input/input_system.hpp"
#include "../src/image/image_loader.hpp"
#include "../src/sprite/object.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/system_impl.hpp"
#include "../src/sprite/texture_animation.hpp"
#include "../src/texture/manager.hpp"
#include "../src/texture/util.hpp"
#include "../src/texture/no_fragmented_texture.hpp"
#include "../src/texture/default_creator.hpp"
#include "../src/texture/default_creator_impl.hpp"

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(1024, 768);
	sys.init<sge::init::input>();
	sys.init<sge::init::image_loader>();
	
	const sge::input_system_ptr is   = sys.input_system;
	const sge::renderer_ptr     rend = sys.renderer;
	const sge::image_loader_ptr pl   = sys.image_loader;

	const sge::image_ptr img1(pl->load_image(sge::media_path() / SGE_TEXT("cloudsquare.jpg"))),
	                     img2(pl->load_image(sge::media_path() / SGE_TEXT("grass.png")));

	const sge::default_texture_creator<sge::no_fragmented_texture> creator(rend, sge::linear_filter);
	sge::texture_manager tex_man(rend, creator);

	const sge::virtual_texture_ptr tex1(sge::add_texture(tex_man, img1)),
	                               tex2(sge::add_texture(tex_man, img2));

	sge::sprite::system ss(rend);
	sge::sprite::object spr(
		sge::sprite::point(0,rend->screen_height()),
        	sge::virtual_texture_ptr(),
		sge::sprite::dim(rend->screen_width(), -rend->screen_height()));

	const sge::sprite::texture_animation::animation_series series(
		boost::assign::list_of
			(sge::sprite::texture_animation::entity(sge::second() / 2, tex1))
			(sge::sprite::texture_animation::entity(sge::second(), tex2))
		.to_container(series)
	);
	sge::sprite::texture_animation anim(series, &spr);

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	bool running = true;

	const sge::scoped_connection cb(
		is->register_callback(
			if_(bind(&sge::key_type::code,
				bind(&sge::key_pair::key,boost::lambda::_1))
			== sge::kc::key_escape)
		[var(running)=false])
	);

	rend->set_state((
		sge::bool_state::clear_backbuffer = true,
		sge::depth_func::off,
		sge::cull_mode::off));
	rend->projection(sge::math::matrix_orthogonal_xy());

	while(running)
	{
		const sge::scoped_renderblock block_(rend);
		sge::window::dispatch();
		is->dispatch();
		anim.process();
		ss.render(&spr, &spr+1);
	}
}
catch(const std::exception& e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
