/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/systems/viewport/manage_resize.hpp>
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
#include <sge/renderer/no_depth_stencil_texture.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/no_program.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/log/global.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
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
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/window/instance.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <sge/multi_loader.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

//#include <sge/renderer/glsl/uniform/array_value.hpp>
#include <fcppt/math/matrix/matrix.hpp>
#include <vector>

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
	FCPPT_NONASSIGNABLE(
		sprite_functor
	)
public:
	explicit sprite_functor(
		sprite_object &_sprite
	)
	:
		sprite_(_sprite)
	{}

	void
	operator()(
		sge::input::mouse::axis_event const &_event
	) const
	{
		switch (_event.axis())
		{
		case sge::input::mouse::axis::x:
			sprite_.x(
				sprite_.x()
				+ _event.axis_position()
			);
			break;
		case sge::input::mouse::axis::y:
			sprite_.y(
				sprite_.y()
				+ _event.axis_position()
			);
			break;
		default:
			break;
		}
	}
private:
	sprite_object &sprite_;
};
}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::renderer::screen_size const screen_size(
		1024,
		768
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge dopplertest")
				)
			)
		)
		(
			sge::systems::renderer(
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
				),
				sge::systems::viewport::manage_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
				(
					FCPPT_TEXT("jpg")
				)
			)
		)
	);

	sge::image::file_ptr const
		image_bg(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("shadertest.jpg")
			)
		),
		image_pointer(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("gui")
				/ FCPPT_TEXT("cursor.png")
			)
		),
		image_tux(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("tux.png")
			)
		);

	sge::texture::manager tex_man(
		sys.renderer(),
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(

				sys.renderer(),
				sge::image::color::format::rgba8,
				sge::renderer::filter::linear
			)
		)
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
			(sge::image::color::init::red %= 1.0)
			(sge::image::color::init::green %= 1.0)
			(sge::image::color::init::blue %= 1.0)
			(sge::image::color::init::alpha %= 0.25)
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	fcppt::signal::scoped_connection const pc(
		sys.mouse_collector()->axis_callback(
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

	sge::renderer::texture_ptr const target_texture(
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

	sge::renderer::target_ptr const target(
		sys.renderer()->create_target(
			target_texture,
			sge::renderer::no_depth_stencil_texture()
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
				target_texture
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

	fcppt::io::cifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("fragment.glsl")
	);

	fcppt::io::cifstream vertex_stream(
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

#if 0
	std::vector<
		fcppt::math::matrix::static_<
			float,
			3,
			3
		>::type
	> matrix_vector;

	sge::renderer::glsl::uniform::array_value(
		v,
		matrix_vector
	);
#endif

	while(running)
	{
		sys.window()->dispatch();
		{
			sys.renderer()->glsl_program(
				sge::renderer::glsl::no_program()
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
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
