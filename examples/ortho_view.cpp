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


#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/log/global.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
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
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/states.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::window::dim const window_dim(
		1024,
		768);

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge orthographic camera test")),
					window_dim)))
		(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::center_on_resize(
					window_dim)))
		(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive)))
		(sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("png"))))))
		(sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("ogg")))))));

	sge::camera::ortho_freelook::object camera(
		sge::camera::ortho_freelook::parameters(
			sys.mouse_collector(),
			sys.keyboard_collector(),
			sge::renderer::projection::rect(
				sge::renderer::projection::rect::vector::null(),
				sge::renderer::projection::rect::dim(
					static_cast<sge::renderer::scalar>(
						window_dim.w()),
					static_cast<sge::renderer::scalar>(
						window_dim.h())))));

	sge::texture::manager tex_man(
		boost::phoenix::construct<sge::texture::fragmented_unique_ptr>(
			boost::phoenix::new_<sge::texture::no_fragmented>(
				fcppt::ref(
					sys.renderer()),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off())));

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*sys.image_system().load(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("grass.png")))),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				*sys.image_system().load(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("tux.png"))));

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
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::normal
			>
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

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
		.texture(
			tex_bg)
		.pos(
			sprite_object::vector::null())
		.size(
			fcppt::math::dim::structure_cast<sprite_object::dim>(
				window_dim))
	);

	sprite_object const tux(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				static_cast<sprite_object::unit>(
					window_dim.w() / 2 - 16u),
				static_cast<sprite_object::unit>(
					window_dim.h() / 2 -16u)))
		.texture(
			tex_tux)
		.size(
			sprite_object::dim(32,32))
	);

	bool running =
		true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black()));

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::duration(
				1.0f)));

	while(running)
	{
		sys.window_system().poll();

		camera.update(
			sge::timer::elapsed<sge::camera::duration>(
				camera_timer));

		sge::renderer::scoped_block const block_(
			sys.renderer());

		sge::renderer::scoped_transform projection_transform(
			sys.renderer(),
			sge::renderer::matrix_mode::projection,
			camera.projection());

		sge::renderer::scoped_transform world_transform(
			sys.renderer(),
			sge::renderer::matrix_mode::world,
			camera.world());

		sge::renderer::state::scoped scoped_state(
			sys.renderer(),
			sge::sprite::render::states<
				sprite_choices
			>()
		);

		typedef sge::sprite::process::options<
			sge::sprite::process::geometry_options::fill,
			sge::sprite::render::options<
				sge::sprite::render::matrix_options::nothing,
				sge::sprite::render::state_options::nothing,
				sge::sprite::render::vertex_options::declaration_and_buffer
			>
		> sprite_options;

		sge::sprite::process::one_with_options<
			sprite_options
		>(
			background,
			sprite_buffers.buffers()
		);

		sge::sprite::process::one_with_options<
			sprite_options
		>(
			tux,
			sprite_buffers.buffers()
		);
	}
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
