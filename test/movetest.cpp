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
#include <cmath>
#include <algorithm>
#include <exception>
#include <ostream>
#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/assign/list_of.hpp>
#include "../src/math/rect_impl.hpp"
#include "../src/systems.hpp"
#include "../src/init.hpp"
#include "../src/media.hpp"
#include "../src/scoped_connection.hpp"
#include "../src/window.hpp"
#include "../src/math/constants.hpp"
#include "../src/math/utility.hpp"
#include "../src/renderer/renderer.hpp"
#include "../src/renderer/scoped_renderblock.hpp"
#include "../src/input/input_system.hpp"
#include "../src/input/key_type.hpp"
#include "../src/image/image_loader.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/system_impl.hpp"
#include "../src/texture/default_creator.hpp"
#include "../src/texture/default_creator_impl.hpp"
#include "../src/texture/manager.hpp"
#include "../src/texture/virtual_texture.hpp"
#include "../src/texture/no_fragmented_texture.hpp"
#include "../src/texture/util.hpp"

struct input_processor {
	input_processor(const sge::renderer_ptr rend, const sge::input_system_ptr is, sge::sprite& spr, sge::sprite& mouse)
	: rend(rend),
	  cb(is->register_callback(boost::bind(&input_processor::process, this, _1))),
	  spr(spr),
	  mouse(mouse)
	{}
private:
	void process(const sge::key_pair& pair)
	{
		const sge::key_code code = pair.key().code();
		const sge::key_state value = pair.value();

		if(!sge::is_mouse_axis(code))
			return;
		switch(code) {
		case sge::kc::mouse_x_axis:
			mouse.x() += static_cast<sge::sprite_unit>(value);
			break;
		case sge::kc::mouse_y_axis:
			mouse.y() += static_cast<sge::sprite_unit>(value);
			break;
		default:
			break;
		}

		sge::math::clamp(mouse.x(), 0, static_cast<sge::sprite_unit>(rend->screen_width()));
		sge::math::clamp(mouse.y(), 0, static_cast<sge::sprite_unit>(rend->screen_height()));

		const sge::sprite_point d = spr.center() - mouse.pos();
		const sge::space_unit len = sge::math::structure_cast<sge::space_unit>(d).length();
		if(sge::math::almost_zero(len))
			return;
		const sge::space_unit rad = std::asin(d.x() / len);
		spr.rotation(d.y() >= 0 ? rad : -rad + sge::math::pi<sge::space_unit>());
	}

	const sge::renderer_ptr rend;
	const sge::scoped_connection cb;
	sge::sprite& spr;
	sge::sprite& mouse;
};

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

	sge::texture_manager tex_man(rend, sge::default_texture_creator<sge::no_fragmented_texture>(rend, sge::linear_filter));

	const sge::virtual_texture_ptr tex(sge::add_texture(tex_man, pl->load_image(sge::media_path("cloudsquare.jpg")))),
	                               cursor_tex(sge::add_texture(tex_man, pl->load_image(sge::media_path("mainskin/cursor.png"))));

	sge::sprite_system ss(rend);
	const sge::sprite_unit spr_sz = 50;
	sge::sprite spr(sge::sprite::point(rend->screen_width() / 2, rend->screen_height() / 2),
	                sge::sprite::dim(spr_sz, spr_sz),
	                tex),
	            cursor(sge::sprite::point(50, 50),
	                   sge::sprite::dim(32, 32),
	                   cursor_tex);
	
	const input_processor proc(rend, is, spr, cursor);

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	bool running = true;

	const sge::scoped_connection cb(
		is->register_callback(
			if_(bind(&sge::key_type::code,
				bind(&sge::key_pair::key, boost::lambda::_1))
			== sge::kc::key_escape)
		[var(running)=false])
	);

	rend->set_bool_state(sge::bool_state::clear_backbuffer, true);
	rend->set_bool_state(sge::bool_state::enable_zbuffer, false);
	rend->set_bool_state(sge::bool_state::enable_culling, false);
	rend->projection(sge::math::matrix_orthogonal_xy());

	while(running)
	{
		sge::window::dispatch();
		is->dispatch();

		const sge::scoped_renderblock block_(rend);
		std::vector<sge::sprite> sprites(boost::assign::list_of(spr)(cursor).to_container(sprites));
		ss.render(sprites.begin(), sprites.end());
	}
}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}
