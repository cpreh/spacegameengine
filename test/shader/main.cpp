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
#include <fcppt/io/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/log/global.hpp>
#include <sge/log/activate_levels.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_code.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/render_one.hpp>
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
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

namespace
{

typedef sge::image::color::rgba8_format sprite_color;

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector3<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_depth
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class sprite_functor
{
public:
	explicit sprite_functor(
		sprite_object &s
	)
	:
		s(s)
	{}

	void
	operator()(
		sge::input::key_pair const &k
	) const
	{
		switch (k.key().code())
		{
		case sge::input::kc::mouse_x_axis:
			s.x(
				s.x() + k.value()
			);
			break;
		case sge::input::kc::mouse_y_axis:
			s.y(
				s.y() + k.value()
			);
			break;
		default:
			break;
		}
	}
private:
	sprite_object &s;
};
}

int main()
try
{
	sge::log::activate_levels(
		sge::log::global(),
		sge::log::level::debug
	);

	sge::renderer::screen_size const screen_size(
		1024,
		768
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge dopplertest")
			)
		)
		(
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
			)
		)
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image)
	);

	sge::image::file_ptr const
		image_bg(
			sys.image_loader()->load(
				sge::config::media_path()
				/ FCPPT_TEXT("shadertest.jpg")
			)
		),
		image_pointer(
			sys.image_loader()->load(
				sge::config::media_path()
				/ FCPPT_TEXT("gui")
				/ FCPPT_TEXT("cursor.png")
			)
		),
		image_tux(
			sys.image_loader()->load(
				sge::config::media_path()
				/ FCPPT_TEXT("tux.png")
			)
		);

	sge::texture::default_creator<
		sge::texture::no_fragmented
	> const
		creator(
			sys.renderer(),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear
		);

	sge::texture::manager tex_man(
		sys.renderer(),
		creator
	);

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				image_bg
			)
		),
		tex_pointer(
			sge::texture::add_image(
				tex_man,
				image_pointer
			)
		),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				image_tux
			)
		);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss(
		sys.renderer()
	);

	sprite_object bg(
		sprite_parameters()
			.pos(
				sprite_object::point::null()
			)
			.texture(
				tex_bg
			)
			.size(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					screen_size
				)
			)
			.depth(
				static_cast<
					sprite_object::depth_type
				>(2)
			)
			.elements()
		);

	sprite_object pointer(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			tex_pointer
		)
		.texture_size()
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(0)
		)
		.elements()
	);

	sprite_object tux(
		sprite_parameters()
		.pos(
			sprite_object::point(
				screen_size.w()/2-16,
				screen_size.h()/2-16
			)
		)
		.texture(
			tex_tux
		)
		.size(
			sprite_object::dim(32,32)
		)
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
		.elements()
	);

	tux.color(
		sge::image::color::rgba8(
			sge::image::color::init::red %= 1.0,
			sge::image::color::init::green %= 1.0,
			sge::image::color::init::blue %= 1.0,
			sge::image::color::init::alpha %= 0.25
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
				pointer
			)
		)
	);

	/*
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::renderer::rgba8_color(0, 0, 0, 0))
	);
	*/

	sge::renderer::texture_ptr const target(
		sys.renderer()->create_texture(
			fcppt::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				screen_size
			),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::none
		)
	);

	sprite_object target_spr(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				target
			)
		)
		.texture_size()
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
		.elements()
	);

	sge::cifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("fragment.glsl")
	);

	sge::cifstream vertex_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("vertex.glsl")
	);

	sge::renderer::glsl::program_ptr const p(
		sys.renderer()->create_glsl_program(
			sge::renderer::glsl::istream_ref(
				vertex_stream
			),
			sge::renderer::glsl::istream_ref(
				fragment_stream
			)
		)
	);

	sys.renderer()->glsl_program(
		p
	);

	sge::renderer::glsl::uniform::variable_ptr const v(
		p->uniform("tex")
	);

	sge::renderer::glsl::uniform::single_value(
		v,
		static_cast<int>(0)
	);

	while(running)
	{
		sge::mainloop::dispatch();
		{
			sys.renderer()->glsl_program(
				sge::renderer::device::no_program
			);

			sge::renderer::scoped_block const block_(
				sys.renderer()
			);

			sge::renderer::scoped_target const target_(
				sys.renderer(),
				target
			);

			typedef std::vector<
				sprite_object
			> sprite_container;
			
			sprite_container sprites;

			sprites.push_back(bg);
			sprites.push_back(pointer);
			sprites.push_back(tux);

			ss.render(
				sprites.begin(),
				sprites.end(),
				sge::sprite::default_sort(),
				sge::sprite::default_equal()
			);
		}

		sys.renderer()->glsl_program(
			p
		);

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			target_spr
		);
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
