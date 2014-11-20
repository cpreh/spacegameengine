/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/buffer.hpp>
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
#include <sge/image/color/predef.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/relative_move_event.hpp>
#include <sge/input/cursor/relative_movement.hpp>
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
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/step.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

class cursor_speed_tracker
{
FCPPT_NONCOPYABLE(
	cursor_speed_tracker);
public:
	typedef
	float
	scalar;

	typedef
	std::function<scalar(scalar)>
	modifier;

	cursor_speed_tracker(
		sge::input::cursor::object &,
		modifier const &);

	void
	update();

	scalar
	current_speed() const;
private:
	typedef
	boost::circular_buffer<scalar>
	speed_ring_buffer;

	modifier const modifier_;
	sge::input::cursor::relative_movement relative_cursor_movement_;
	fcppt::signal::scoped_connection relative_movement_connection_;
	speed_ring_buffer speed_values_;
	scalar current_speed_;
	bool speed_updated_;

	void
	move_callback(
		sge::input::cursor::relative_move_event const &);
};

}

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

cursor_speed_tracker::cursor_speed_tracker(
	sge::input::cursor::object &_cursor,
	modifier const &_modifier)
:
	modifier_(
		_modifier),
	relative_cursor_movement_(
		_cursor),
	relative_movement_connection_(
		relative_cursor_movement_.relative_move_callback(
			std::bind(
				&cursor_speed_tracker::move_callback,
				this,
				std::placeholders::_1))),
	speed_values_(
		static_cast<speed_ring_buffer::capacity_type>(
			10u)),
	current_speed_(
		0.0f),
	speed_updated_(
		false)
{
	// Eliminate nasty / 0 in current_speed
	speed_values_.push_back(
		modifier_(
			0.0f));
}

FCPPT_PP_POP_WARNING

void
cursor_speed_tracker::move_callback(
	sge::input::cursor::relative_move_event const &_e)
{
	typedef
	fcppt::math::vector::static_<scalar,2>
	vector2;

	current_speed_ =
		static_cast<scalar>(
			fcppt::math::vector::length(
				fcppt::math::vector::structure_cast<vector2>(
					_e.position())));

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
				static_cast<scalar>(
					0.0f)));

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
			static_cast<scalar>(
				0)) /
		static_cast<scalar>(
			speed_values_.size());
}

}

namespace
{
cursor_speed_tracker::scalar
cursor_speed_modifier(
	cursor_speed_tracker::scalar const _input)
{
	cursor_speed_tracker::scalar const
		initial_value =
			std::pow(
				_input / 100.0f,
				0.5f),
		final_value =
			fcppt::math::step(
				initial_value,
				0.25f) *
			initial_value;

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
		boost::mpl::vector6<
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::keyboard_collector,
					sge::systems::cursor_demuxer
				>
			>,
			sge::systems::with_audio_player,
			sge::systems::with_audio_loader,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("sge dopplertest")
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
				5,
				5)),
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

	sge::input::cursor::object &cursor(
		sys.cursor_demuxer()
	);

	sge::texture::const_part_unique_ptr const
		tex_bg(
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
		),
		tex_tux(
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
		sge::sprite::config::normal_size,
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
	> sprite_buffers;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	typedef sge::sprite::state::all_choices sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state_object;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	sprite_buffers sprite_buf(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

	sprite_state_object sprite_states(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sprite_object const background(
		sprite_parameters()
		.texture(
			sprite_object::texture_type(
				*tex_bg
			)
		)
		.pos(
			sprite_object::vector::null()
		)
		.texture_size()
	);

	sprite_object const tux(
		sprite_parameters()
		.pos(
			// FIXME
			fcppt::math::vector::fill<
				sprite_object::vector
			>(
				100
			)
		)
		.texture(
			sprite_object::texture_type(
				*tex_tux
			)
		)
		.texture_size()
	);

	sge::audio::file_unique_ptr const af_siren(
		sge::audio::load_exn(
			sys.audio_loader(),
			sge::config::media_path()
			/ FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("wind.wav")
		)
	);

	sge::audio::buffer_unique_ptr const sound_buffer(
		sys.audio_player().create_buffer(
			*af_siren));

	sge::audio::sound::base_unique_ptr const sound_siren(
		sound_buffer->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()));

	sound_siren->play(
		sge::audio::sound::repeat::loop
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	cursor_speed_tracker cursor_speed(
		cursor,
		&cursor_speed_modifier
	);

	sound_siren->pitch(
		fcppt::literal<
			sge::audio::scalar
		>(
			0
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
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
			scoped_block.get());

		/*
		std::cout << "current speed: " << cursor_speed.current_speed() << "\n";
		cursor_speed_tracker::scalar const
			initial_value =
				std::pow(
					cursor_speed.current_speed() / 100.0f,
					0.5f),
			final_value =
				fcppt::math::step(
					initial_value,
					0.25f) *
				initial_value;
		*/

		graph.push(
			cursor_speed.current_speed());
		sound_siren->pitch(
			cursor_speed.current_speed());
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
