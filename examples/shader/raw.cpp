/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_scoped_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/log/global.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/glsl/const_optional_program_ref.hpp>
#include <sge/renderer/glsl/pixel_shader.hpp>
#include <sge/renderer/glsl/pixel_shader_scoped_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/program_scoped_ptr.hpp>
#include <sge/renderer/glsl/scoped_attachment.hpp>
#include <sge/renderer/glsl/vertex_shader.hpp>
#include <sge/renderer/glsl/vertex_shader_scoped_ptr.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/variable_scoped_ptr.hpp>
#include <sge/renderer/target/from_texture.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/offscreen_scoped_ptr.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/const_part_scoped_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef sge::image::color::rgba8_format sprite_color_format;

typedef sge::sprite::config::choices<
	sge::sprite::config::type_choices<
		sge::sprite::config::unit_type<
			int
		>,
		sge::sprite::config::float_type<
			float
		>
	>,
	sge::sprite::config::normal_size,
	boost::mpl::vector2<
		sge::sprite::config::with_color<
			sprite_color_format
		>,
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::reference
		>
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class sprite_functor
{
	FCPPT_NONASSIGNABLE(
		sprite_functor
	);
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
		switch (_event.code())
		{
		case sge::input::mouse::axis_code::x:
			sprite_.x(
				static_cast<sprite_object::unit>(
					sprite_.x() + _event.value()));
			break;
		case sge::input::mouse::axis_code::y:
			sprite_.y(
				static_cast<sprite_object::unit>(
					sprite_.y() + _event.value()));
			break;
		default:
			break;
		}
	}
private:
	sprite_object &sprite_;
};
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge raw glsl shader test")
					),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32
					),
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
					(
						sge::media::extension(
							FCPPT_TEXT("jpg")
						)
					)
				)
			)
		)
	);

	sge::image2d::file_scoped_ptr const
		image_bg(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("shadertest.jpg")
			)
		),
		image_pointer(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("cursor.png")
			)
		),
		image_tux(
			sys.image_system().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("tux.png")
			)
		);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					sys.renderer()
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off()
			)
		)
	);

	sge::texture::const_part_scoped_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*image_bg
			)
		),
		tex_pointer(
			sge::texture::add_image(
				tex_man,
				*image_pointer
			)
		),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				*image_tux
			)
		);

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_buffers_type sprite_buffers(
		sys.renderer(),
		sge::sprite::buffers::option::dynamic
	);

	sprite_object const background(
		sprite_parameters()
			.pos(
				sprite_object::vector::null()
			)
			.texture(
				sprite_object::texture_type(
					*tex_bg
				)
			)
			.size(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					window_dim
				)
			)
			.default_color()
		);

	sprite_object pointer(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			sprite_object::texture_type(
				*tex_pointer
			)
		)
		.texture_size()
		.default_color()
	);

	sprite_object tux(
		sprite_parameters()
		.pos(
			sprite_object::vector(
 				static_cast<sprite_object::unit>(
					window_dim.w()/2-16),
 				static_cast<sprite_object::unit>(
					window_dim.h()/2-16)
			)
		)
		.texture(
			sprite_object::texture_type(
				*tex_tux
			)
		)
		.size(
			sprite_object::dim(32,32)
		)
		.color(
			sge::image::color::rgba8(
				(sge::image::color::init::red() %= 1.0)
				(sge::image::color::init::green() %= 1.0)
				(sge::image::color::init::blue() %= 1.0)
				(sge::image::color::init::alpha() %= 0.25)
			)
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	fcppt::signal::scoped_connection const pc(
		sys.mouse_collector().axis_callback(
			sprite_functor(
				pointer
			)
		)
	);

	sge::renderer::texture::planar_scoped_ptr const target_texture(
		sys.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<
					sge::renderer::dim2
				>(
					window_dim
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target
				)
			)
		)
	);

	sge::renderer::target::offscreen_scoped_ptr const target(
		sge::renderer::target::from_texture(
			sys.renderer(),
			*target_texture
		)
	);

	sge::texture::const_part_scoped_ptr const target_texture_part(
		fcppt::make_unique_ptr<
			sge::texture::part_raw
		>(
			fcppt::ref(
				*target_texture
			)
		)
	);

	sprite_object target_spr(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			sprite_object::texture_type(
				*target_texture_part
			)
		)
		.texture_size()
		.default_color()
	);

	boost::filesystem::ifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("raw")
		/ FCPPT_TEXT("fragment.glsl")
	);

	boost::filesystem::ifstream vertex_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("raw")
		/ FCPPT_TEXT("vertex.glsl")
	);

	sge::renderer::glsl::program_scoped_ptr const program(
		sys.renderer().create_glsl_program()
	);

	sge::renderer::glsl::vertex_shader_scoped_ptr const vertex_shader(
		sys.renderer().create_glsl_vertex_shader(
			fcppt::io::stream_to_string(
				vertex_stream
			)
		)
	);

	vertex_shader->compile();

	sge::renderer::glsl::pixel_shader_scoped_ptr const pixel_shader(
		sys.renderer().create_glsl_pixel_shader(
			fcppt::io::stream_to_string(
				fragment_stream
			)
		)
	);

	pixel_shader->compile();

	program->vertex_declaration(
		sprite_buffers.parameters().vertex_declaration()
	);

	sge::renderer::glsl::scoped_attachment const vertex_shader_attachment(
		*program,
		*vertex_shader
	);

	sge::renderer::glsl::scoped_attachment const pixel_shader_attachment(
		*program,
		*pixel_shader
	);

	program->link();

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::clear::parameters const clear_parameters(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()));

		{
			sge::renderer::context::scoped const scoped_block(
				sys.renderer(),
				*target);

			// TODO: is this really necessary
			scoped_block.get().glsl_program(
				sge::renderer::glsl::const_optional_program_ref(
					*program
				)
			);

			sge::renderer::glsl::uniform::variable_scoped_ptr const tex_var(
				program->uniform("tex")
			);

			sge::renderer::glsl::uniform::single_value(
				*tex_var,
				static_cast<int>(0)
			);

			scoped_block.get().glsl_program(
				sge::renderer::glsl::const_optional_program_ref()
			);

			scoped_block.get().clear(
				clear_parameters
			);

			sge::sprite::process::one(
				scoped_block.get(),
				background,
				sprite_buffers
			);

			sge::sprite::process::one(
				scoped_block.get(),
				tux,
				sprite_buffers
			);

			sge::sprite::process::one(
				scoped_block.get(),
				pointer,
				sprite_buffers
			);
		}

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target());

		scoped_block.get().glsl_program(
			sge::renderer::glsl::const_optional_program_ref(
				*program
			)
		);

		scoped_block.get().clear(
			clear_parameters
		);

		sge::sprite::process::one(
			scoped_block.get(),
			target_spr,
			sprite_buffers
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
