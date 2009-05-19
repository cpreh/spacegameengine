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



#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/log/headers.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_code.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/fstream.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

namespace
{
class sprite_functor
{
	public:
	explicit sprite_functor(
		sge::sprite::object &s)
		:
			s(s)
		{}

	void operator()(sge::input::key_pair const &k) const
	{
		switch (k.key().code())
		{
			case sge::input::kc::mouse_x_axis:
			s.pos().x() += k.value();
			break;
			case sge::input::kc::mouse_y_axis:
			s.pos().y() += k.value();
			break;
			default: break;
		}
	}
	private:
	sge::sprite::object &s;
};
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);
	sge::renderer::screen_size const screen_size(1024,768);
	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge dopplertest")
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
		(sge::systems::parameterless::image));
	
	sge::image::file_ptr const 
		image_bg(
			sys.image_loader()->load(
				sge::config::media_path()/SGE_TEXT("shadertest.jpg"))),
		image_pointer(
			sys.image_loader()->load(
				sge::config::media_path()/SGE_TEXT("gui")/SGE_TEXT("cursor.png"))),
		image_tux(
			sys.image_loader()->load(
				sge::config::media_path()/SGE_TEXT("tux.png")));

	sge::texture::default_creator<sge::texture::no_fragmented> const 
		creator(
			sys.renderer(),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear);

	sge::texture::manager tex_man(sys.renderer(),creator);

	sge::texture::const_part_ptr const 
		tex_bg(
			sge::texture::add_image(
				tex_man, 
				image_bg)),
		tex_pointer(
			sge::texture::add_image(
				tex_man, 
				image_pointer)),
		tex_tux(
			sge::texture::add_image(
				tex_man, 
				image_tux));
	
	sge::sprite::system ss(sys.renderer());

	sge::sprite::object bg(
		sge::sprite::parameters()
			.texture(tex_bg)
			.size(
				sge::math::dim::structure_cast<sge::sprite::dim>(
					screen_size))
			.depth(
				static_cast<sge::sprite::depth_type>(2)));

	sge::sprite::object pointer(
		sge::sprite::parameters()
			.texture(
				tex_pointer)
			.depth(
				static_cast<sge::sprite::depth_type>(0)));

	sge::sprite::object tux(
		sge::sprite::parameters()
			.pos(
				sge::sprite::point(screen_size.w()/2-16,screen_size.h()/2-16))
			.texture(
				tex_tux)
			.size(
				sge::sprite::dim(32,32))
			.depth(
				static_cast<sge::sprite::depth_type>(1)));
	
	tux.color(
		sge::image::color::rgba8(
			0xff,
			0xff,
			0xff,
			0x40
		)
	);

	bool running = true;

	sge::signal::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::signal::scoped_connection const pc(
		sys.input_system()->register_callback(
			sprite_functor(
				pointer)));

	/*
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::renderer::rgba8_color(0, 0, 0, 0))
	);
	*/

	sge::renderer::texture_ptr const target(
		sys.renderer()->create_texture(
			sge::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				screen_size
			),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::none
		)
	);
	
	sge::sprite::object target_spr(
		sge::sprite::parameters()
			.texture(
				sge::make_shared_ptr<
					sge::texture::part_raw
				>(
					target
				)
			)
			.depth(
				static_cast<sge::sprite::depth_type>(1)
			)
	);
	
	sge::cifstream fragment_stream(
		sge::config::media_path()/SGE_TEXT("shaders")/SGE_TEXT("fragment.glsl"));
	sge::cifstream vertex_stream(
		sge::config::media_path()/SGE_TEXT("shaders")/SGE_TEXT("vertex.glsl"));

	sge::renderer::glsl::program_ptr const p = 
		sys.renderer()->create_glsl_program(
			sge::renderer::glsl::istream_ref(vertex_stream),
			sge::renderer::glsl::istream_ref(fragment_stream));
	
	sys.renderer()->glsl_program(
		p);

	sge::renderer::glsl::uniform::variable_ptr const v = 
		p->uniform("tex");
	
	sge::renderer::glsl::uniform::single_value(
		v,
		static_cast<int>(0)
	);

	while(running)
	{
		sge::mainloop::dispatch();
		{
			sys.renderer()->glsl_program(
				sge::renderer::device::no_program);

			sge::renderer::scoped_block const block_(
				sys.renderer());

			sge::renderer::scoped_target const target_(
				sys.renderer(),
				target);

			sge::sprite::container sprites;
			sprites.push_back(bg);
			sprites.push_back(pointer);
			sprites.push_back(tux);
			ss.render(sprites.begin(),sprites.end());
		}

		sys.renderer()->glsl_program(
			p);

		sge::renderer::scoped_block const block_(sys.renderer());

		ss.render(
			target_spr);
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
