//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/ortho_freelook/projection_rectangle_from_viewport.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/event/key.hpp>
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
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
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
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
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
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <metal.hpp>
#include <chrono>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input,
		sge::systems::with_image2d
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge orthographic camera test")
						)
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
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
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
			sge::renderer::projection::near(
				0.0f
			),
			sge::renderer::projection::far(
				10.0f
			)
		)
	);

	sge::camera::ortho_freelook::projection_rectangle_from_viewport const projection_rectangle_from_viewport(
		fcppt::make_ref(
			camera
		),
		fcppt::make_ref(
			sys.viewport_manager()
		)
	);

	sge::texture::const_part_unique_ptr const tex_bg(
		fcppt::unique_ptr_to_const(
			fcppt::unique_ptr_to_base<
				sge::texture::part
			>(
				fcppt::make_unique_ptr<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_path(
						sge::config::media_path()
						/ FCPPT_TEXT("images")
						/ FCPPT_TEXT("grass.png"),
						fcppt::make_ref(
							sys.renderer_device_core()
						),
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
				fcppt::make_unique_ptr<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_path(
						sge::config::media_path()
						/ FCPPT_TEXT("images")
						/ FCPPT_TEXT("tux.png"),
						fcppt::make_ref(
							sys.renderer_device_core()
						),
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

	typedef
	sge::sprite::config::choices<
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
		metal::list<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>
	sprite_buffers_type;

	sprite_buffers_type sprite_buffers(
		fcppt::make_ref(
			sys.renderer_device_core()
		),
		sge::sprite::buffers::option::dynamic
	);

	typedef
	sge::sprite::state::all_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state_object;

	typedef
	sge::sprite::state::parameters<
		sprite_state_choices
	>
	sprite_state_parameters;

	sprite_state_object sprite_states(
		fcppt::make_ref(
			sys.renderer_device_ffp()
		),
		sprite_state_parameters()
	);

	sprite_object const background(
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type(
				*tex_bg
			),
		sge::sprite::roles::pos{} =
			fcppt::math::vector::null<
				sprite_object::vector
			>()
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

	auto const grab_cursor(
		[
			&sys
		](
			sge::input::keyboard::event::key const &_event
		)
		{
			if(
				_event.get().code()
				==
				sge::input::key::code::g
			)
				for(
					sge::input::cursor::shared_ptr const &cursor
					:
					sys.input_processor().cursors()
				)
					cursor->mode(
						_event.pressed()
						?
							sge::input::cursor::mode::exclusive
						:
							sge::input::cursor::mode::normal
					);
		}
	);

	sge::timer::basic<
		sge::timer::clocks::standard
	> camera_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	auto const draw_camera(
		[
			&background,
			&camera,
			&sprite_buffers,
			&sprite_states,
			&sys,
			&tux
		](
			sge::renderer::context::ffp &_context,
			sge::camera::projection_matrix const &_projection
		)
		{
			sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						_projection.get()
					)
				)
			);

			sge::renderer::state::ffp::transform::object_unique_ptr const world_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						sge::camera::matrix_conversion::world(
							camera.coordinate_system()
						)
					)
				)
			);

			sge::renderer::state::ffp::transform::scoped const projection_transform(
				// TODO
				fcppt::make_ref(
					_context
				),
				sge::renderer::state::ffp::transform::mode::projection,
				fcppt::make_cref(
					*projection_state
				)
			);

			sge::renderer::state::ffp::transform::scoped const world_transform(
				fcppt::make_ref(
					_context
				),
				sge::renderer::state::ffp::transform::mode::world,
				fcppt::make_cref(
					*world_state
				)
			);

			sge::sprite::state::scoped<
				sprite_state_choices
			> const scoped_state(
				sys.renderer_device_ffp(),
				fcppt::make_ref(
					_context
				),
				sge::sprite::state::default_options<
					sprite_state_choices
				>(),
				sprite_states
			);

			typedef
			sge::sprite::state::options<
				sprite_state_choices
			>
			sprite_state_options;

			sprite_state_options const state_options(
				sge::sprite::state::default_options<
					sprite_state_choices
				>()
				.no_blend_state()
				.no_rasterizer_state()
				.no_transform_state()
			);

			typedef
			sge::sprite::process::options<
				sge::sprite::process::geometry_options::update
			>
			sprite_options;

			sge::sprite::process::one_with_options<
				sprite_options
			>(
				_context,
				background,
				sprite_buffers,
				sprite_states,
				state_options
			);

			sge::sprite::process::one_with_options<
				sprite_options
			>(
				_context,
				tux,
				sprite_buffers,
				sprite_states,
				state_options
			);
		}
	);

	auto const draw(
		[
			&camera,
			&camera_timer,
			&draw_camera,
			&sys
		]{
			camera.update(
				std::chrono::duration_cast<
					sge::camera::update_duration
				>(
					sge::timer::elapsed_and_reset(
						camera_timer
					)
				)
			);

			sge::renderer::context::scoped_ffp const scoped_block(
				fcppt::make_ref(
					sys.renderer_device_ffp()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						sys.renderer_device_ffp().onscreen_target()
					)
				)
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			fcppt::optional::maybe_void(
				camera.projection_matrix(),
				[
					&draw_camera,
					&scoped_block
				](
					sge::camera::projection_matrix const &_projection
				)
				{
					draw_camera(
						scoped_block.get(),
						_projection
					);
				}
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&camera,
					&draw,
					&grab_cursor
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::input::event_base const
						>(
							_event
						),
						[
							&camera
						](
							fcppt::reference<
								sge::input::event_base const
							> const _input_event
						)
						{
							camera.process_event(
								_input_event.get()
							);
						}
					);

					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							metal::list<
								sge::renderer::event::render const,
								sge::input::keyboard::event::key const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&draw,
							&grab_cursor
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								},
								[
									&grab_cursor
								](
									fcppt::reference<
										sge::input::keyboard::event::key const
									> const _key_event
								)
								{
									grab_cursor(
										_key_event.get()
									);
								}
							);
						}
					);
				}
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
