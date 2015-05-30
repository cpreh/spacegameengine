/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/ortho_freelook/projection_rectangle_from_viewport.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/sprite/state/scoped.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/mouse_collector.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <functional>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{
void
g_key_callback(
	sge::input::keyboard::key_event const &e,
	sge::input::cursor::object &c)
{
	if(e.key_code() == sge::input::keyboard::key_code::g)
	{
		c.mode(
			e.pressed()
			?
				sge::input::cursor::mode::exclusive
			:
				sge::input::cursor::mode::normal);
	}
}
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector4<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector3<
					sge::systems::cursor_demuxer,
					sge::systems::keyboard_collector,
					sge::systems::mouse_collector
				>
			>,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("sge orthographic camera test")
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	);

	sge::camera::ortho_freelook::object camera(
		sge::camera::ortho_freelook::parameters(
			sys.mouse_collector(),
			sys.keyboard_collector(),
			sge::renderer::projection::near(
				0.0f),
			sge::renderer::projection::far(
				10.0f),
			sge::camera::is_active(
				true)));

	sge::camera::ortho_freelook::projection_rectangle_from_viewport projection_rectangle_from_viewport(
		camera,
		sys.viewport_manager());

	sge::texture::const_part_unique_ptr const tex_bg(
		fcppt::unique_ptr_to_const(
			fcppt::unique_ptr_to_base<
				sge::texture::part
			>(
				fcppt::make_unique_ptr_fcppt<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_path(
						sge::config::media_path()
						/ FCPPT_TEXT("images")
						/ FCPPT_TEXT("grass.png"),
						sys.renderer_device_ffp(),
						sys.image_system(),
						sge::renderer::texture::mipmap::off(),
						sge::renderer::resource_flags_field::null(),
						sge::renderer::texture::emulate_srgb_from_caps(
							sys.renderer_device_ffp().caps()
						)
					)
				)
			)
		)
	);

	sge::texture::const_part_unique_ptr const tex_tux(
		fcppt::unique_ptr_to_const(
			fcppt::unique_ptr_to_base<
				sge::texture::part
			>(
				fcppt::make_unique_ptr_fcppt<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_path(
						sge::config::media_path()
						/ FCPPT_TEXT("images")
						/ FCPPT_TEXT("tux.png"),
						sys.renderer_device_ffp(),
						sys.image_system(),
						sge::renderer::texture::mipmap::off(),
						sge::renderer::resource_flags_field::null(),
						sge::renderer::texture::emulate_srgb_from_caps(
							sys.renderer_device_ffp().caps()
						)
					)
				)
			)
		)
	);

	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::always
		>,
		boost::mpl::vector1<
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

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	sprite_buffers_type sprite_buffers(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

	typedef sge::sprite::state::all_choices sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state_object;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	sprite_state_object sprite_states(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sprite_object const background(
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type(
				*tex_bg
			),
		sge::sprite::roles::pos{} =
			sprite_object::vector::null()
	);

	sprite_object const tux(
		sge::sprite::roles::pos{} =
			sprite_object::vector(
				32,
				32
			),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type(
				*tex_tux
			)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	fcppt::signal::scoped_connection const grab_connection(
		sys.keyboard_collector().key_callback(
			std::bind(
				&g_key_callback,
				std::placeholders::_1,
				std::ref(
					sys.cursor_demuxer()))));

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::update_duration(
				1.0f)));

	while(
		sys.window_system().poll())
	{
		if(
			sge::renderer::target::viewport_is_null(
				sys.renderer_device_ffp().onscreen_target().viewport()))
			continue;

		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				camera_timer));

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target());

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()));

		sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
			sys.renderer_device_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					camera.projection_matrix().get())));

		sge::renderer::state::ffp::transform::object_unique_ptr const world_state(
			sys.renderer_device_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					sge::camera::matrix_conversion::world(
						camera.coordinate_system()))));

		sge::renderer::state::ffp::transform::scoped const projection_transform(
			scoped_block.get(),
			sge::renderer::state::ffp::transform::mode::projection,
			*projection_state);

		sge::renderer::state::ffp::transform::scoped const world_transform(
			scoped_block.get(),
			sge::renderer::state::ffp::transform::mode::world,
			*world_state);

		sge::sprite::state::scoped<
			sprite_state_choices
		> const scoped_state(
			sys.renderer_device_ffp(),
			scoped_block.get(),
			sge::sprite::state::default_options<
				sprite_state_choices
			>(),
			sprite_states
		);

		typedef sge::sprite::state::options<
			sprite_state_choices
		> sprite_state_options;

		sprite_state_options const state_options(
			sge::sprite::state::default_options<
				sprite_state_choices
			>()
			.no_blend_state()
			.no_rasterizer_state()
			.no_transform_state()
		);

		typedef sge::sprite::process::options<
			sge::sprite::process::geometry_options::update
		> sprite_options;

		sge::sprite::process::one_with_options<
			sprite_options
		>(
			scoped_block.get(),
			background,
			sprite_buffers,
			sprite_states,
			state_options
		);

		sge::sprite::process::one_with_options<
			sprite_options
		>(
			scoped_block.get(),
			tux,
			sprite_buffers,
			sprite_states,
			state_options
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
