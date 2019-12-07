//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/object.hpp>
#include <sge/graph/optional_axis_constraint.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/cursor/relative_movement/event.hpp>
#include <sge/input/cursor/relative_movement/object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
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
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
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
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
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
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
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
#include <fcppt/function.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <cmath>
#include <example_main.hpp>
#include <exception>
#include <metal.hpp>
#include <numeric>
#include <fcppt/config/external_end.hpp>


namespace
{

class cursor_speed_tracker
{
	FCPPT_NONCOPYABLE(
		cursor_speed_tracker
	);
public:
	typedef
	float
	scalar;

	typedef
	fcppt::function<
		scalar(
			scalar
		)
	>
	modifier;

	explicit
	cursor_speed_tracker(
		modifier const &
	);

	void
	update();

	scalar
	current_speed() const;

	void
	move_event(
		sge::input::cursor::relative_movement::event const &
	);
private:
	typedef
	boost::circular_buffer<
		scalar
	>
	speed_ring_buffer;

	modifier const modifier_;

	speed_ring_buffer speed_values_;

	scalar current_speed_;

	bool speed_updated_;

};

}

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

cursor_speed_tracker::cursor_speed_tracker(
	modifier const &_modifier
)
:
	modifier_{
		_modifier
	},
	speed_values_{
		10u
	},
	current_speed_{
		0.0f
	},
	speed_updated_{
		false
	}
{
	// Eliminate nasty / 0 in current_speed
	speed_values_.push_back(
		modifier_(
			0.0f
		)
	);
}

FCPPT_PP_POP_WARNING

void
cursor_speed_tracker::move_event(
	sge::input::cursor::relative_movement::event const &_event
)
{
	typedef
	fcppt::math::vector::static_<
		scalar,
		2
	>
	vector2;

	current_speed_ =
		fcppt::math::vector::length(
			fcppt::math::vector::structure_cast<
				vector2,
				fcppt::cast::int_to_float_fun
			>(
				_event.difference().get()
			)
		);

	speed_updated_ =
		true;
}

void
cursor_speed_tracker::update()
{
	speed_values_.push_back(
		modifier_(
			speed_updated_
			?
				current_speed_
			:
				fcppt::literal<
					scalar
				>(
					0.0f
				)
		)
	);

	speed_updated_ =
		false;
}

cursor_speed_tracker::scalar
cursor_speed_tracker::current_speed() const
{
	return
		std::accumulate(
			speed_values_.begin(),
			speed_values_.end(),
			fcppt::literal<
				scalar
			>(
				0
			)
		)
		/
		fcppt::cast::int_to_float<
			scalar
		>(
			speed_values_.size()
		);
}

}

namespace
{

template<
	typename T
>
T
step(
	T const &_value,
	T const &_vmin
)
{
	return
		_value >= _vmin
		?
			fcppt::literal<
				T
			>(
				1
			)
		:
			fcppt::literal<
				T
			>(
				0
			);
}

cursor_speed_tracker::scalar
cursor_speed_modifier(
	cursor_speed_tracker::scalar const _input
)
{
	cursor_speed_tracker::scalar const
		initial_value{
			std::pow(
				_input / 100.0f,
				0.5f
			)
		},
		final_value{
			step(
				initial_value,
				0.25f
			) *
			initial_value
		};

	return
		final_value;
}
}

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
		sge::systems::with_audio_player,
		sge::systems::with_audio_loader,
		sge::systems::with_image2d
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge dopplertest")
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
			sge::systems::audio_player_default()
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
			sge::systems::audio_loader(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("wav")
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

	sge::graph::object graph(
		sge::graph::position(
			sge::renderer::vector2(
				5.f,
				5.f
			)
		),
		sge::image2d::dim(
			512u,
			128u
		),
		sys.renderer_device_ffp(),
		sge::graph::baseline(
			0.0),
		sge::graph::optional_axis_constraint(),
		sge::graph::color_schemes::bright()
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
				fcppt::make_unique_ptr<
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
	sprite_buffers;

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

	sprite_buffers sprite_buf(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

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
			fcppt::math::vector::null<
				sprite_object::vector
			>()
	);

	sprite_object const tux(
		sge::sprite::roles::pos{} =
			fcppt::math::vector::fill<
				sprite_object::vector
			>(
				100
			),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type(
				*tex_tux
			)
	);

	sge::audio::file_unique_ptr const af_siren(
		sge::audio::load_exn(
			sys.audio_loader(),
			sge::config::media_path()
			/ FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("wind.wav")
		)
	);

	sge::audio::buffer_unique_ptr const sound_buffer{
		sys.audio_player().create_buffer(
			*af_siren
		)
	};

	sge::audio::sound::base_unique_ptr const sound_siren{
		sound_buffer->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()
		)
	};

	sound_siren->play(
		sge::audio::sound::repeat::loop
	);

	cursor_speed_tracker cursor_speed{
		cursor_speed_tracker::modifier{
			&cursor_speed_modifier
		}
	};

	sound_siren->pitch(
		fcppt::literal<
			sge::audio::scalar
		>(
			0
		)
	);

	sge::input::cursor::relative_movement::object const relative_cursor_movement{
		sys.input_processor()
	};

	auto const draw(
		[
			&background,
			&cursor_speed,
			&graph,
			&sound_siren,
			&sprite_buf,
			&sprite_states,
			&sys,
			&tux
		]
		{
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
				background,
				sprite_buf,
				sprite_states
			);

			sge::sprite::process::one(
				scoped_block.get(),
				tux,
				sprite_buf,
				sprite_states
			);

			cursor_speed.update();

			sound_siren->update();

			graph.render(
				scoped_block.get()
			);

			graph.push(
				fcppt::cast::size<
					sge::graph::scalar
				>(
					cursor_speed.current_speed()
				)
			);

			sound_siren->pitch(
				cursor_speed.current_speed()
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&cursor_speed,
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
								sge::input::cursor::relative_movement::event const,
								sge::renderer::event::render const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&cursor_speed,
							&draw
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&cursor_speed
								](
									fcppt::reference<
										sge::input::cursor::relative_movement::event const
									> const _relative_movement
								)
								{
									cursor_speed.move_event(
										_relative_movement.get()
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
