//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
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
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
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
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_window,
		sge::systems::with_input,
		sge::systems::with_image2d
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge sprite tutorial 02")
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
			sge::systems::input(
				sge::systems::cursor_option_field{
					sge::systems::cursor_option::exclusive
				}
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
				sge::sprite::config::texture_ownership::shared
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
		sys.renderer_device_ffp(),
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

	sprite_state_object sprite_state(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sge::image2d::file_unique_ptr const image(
		sge::image2d::load_exn(
			sys.image_system(),
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("tux.png")
		)
	);

	sge::renderer::texture::planar_unique_ptr const image_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer_device_ffp(),
			image->view(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb_from_caps(
				sys.renderer_device_ffp().caps()
			)
		)
	);

	sprite_object my_object(
		sge::sprite::roles::pos{} =
			fcppt::math::vector::null<
				sprite_object::vector
			>(),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type{
				fcppt::make_shared_ptr<
					sge::texture::part_raw_ref
				>(
					*image_texture
				)
			}
	);

	auto const update_pos(
		[
			&my_object
		](
			sge::input::mouse::event::axis const &_event
		)
		{
			auto const update_value(
				[](
					sprite_object::unit const _pos,
					sge::input::mouse::axis_value const _diff
				)
				-> sprite_object::unit
				{
					return
						fcppt::cast::size<
							sprite_object::unit
						>(
							fcppt::cast::size<
								sge::input::mouse::axis_value
							>(
								_pos
							)
							+
							_diff
						);
				}
			);

			switch(
				_event.code()
			)
			{
			case sge::input::mouse::axis_code::x:
				my_object.x(
					update_value(
						my_object.x(),
						_event.value()
					)
				);
				break;
			case sge::input::mouse::axis_code::y:
				my_object.y(
					update_value(
						my_object.y(),
						_event.value()
					)
				);
				break;
			case sge::input::mouse::axis_code::wheel:
			case sge::input::mouse::axis_code::unknown:
				break;
			}
		}
	);

	auto const draw(
		[
			&my_object,
			&sprite_buffers,
			&sprite_state,
			&sys
		]{
			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			sge::sprite::process::one(
				scoped_block.get(),
				my_object,
				sprite_buffers,
				sprite_state
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&update_pos,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							metal::list<
								sge::input::mouse::event::axis const,
								sge::renderer::event::render const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&update_pos,
							&draw
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&update_pos
								](
									fcppt::reference<
										sge::input::mouse::event::axis const
									> const _axis_event
								)
								{
									update_pos(
										_axis_event.get()
									);
								},
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								}
							);
						}
					);
				}
			}
		);
}
catch(
	fcppt::exception const &_exception
)
{
	awl::show_error(
		_exception.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_exception
)
{
	awl::show_error_narrow(
		_exception.what()
	);

	return
		awl::main::exit_failure();
}
