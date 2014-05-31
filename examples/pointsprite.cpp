/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/log/location.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/shader/context.hpp>
#include <sge/shader/optional_cflags.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/parameter/is_projection_matrix.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/custom_texture_point_pos.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/no_texture_point_size.hpp>
#include <sge/sprite/config/point_size.hpp>
#include <sge/sprite/config/point_size_fwd.hpp>
#include <sge/sprite/config/size_choice.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_texture_point_size.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/config.hpp>
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
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_scoped_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/remaining_fractional.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <mizuiro/color/operators/scalar_multiply.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <chrono>
#include <cmath>
#include <example_main.hpp>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
std::chrono::duration<sge::renderer::scalar>
float_duration;

namespace sprite_types
{
typedef
sge::sprite::config::choices
<
	sge::sprite::config::type_choices
	<
		sge::sprite::config::unit_type
		<
			sge::renderer::scalar
		>,
		sge::sprite::config::float_type
		<
			sge::renderer::scalar
		>
	>,
	sge::sprite::config::point_size
	<
		sge::renderer::vf::index
		<
			fcppt::literal
			<
				sge::renderer::vf::vertex_size
			>
			(
				0u
			)
		>
	>,
	boost::mpl::vector2
	<
		sge::sprite::config::with_color
		<
			sge::image::color::rgba8_format
		>,
		sge::sprite::config::with_texture_point_size
		<
			sge::sprite::config::texture_level_count
			<
				1u
			>,
			sge::sprite::config::custom_texture_point_pos
			<
				false
			>,
			sge::sprite::config::no_texture_point_size,
			sge::sprite::config::texture_ownership::reference
		>
	>
>
choices;

typedef
sge::sprite::buffers::with_declaration
<
	sge::sprite::buffers::single<sprite_types::choices>
>
buffers_type;

typedef
sge::sprite::object
<
	sprite_types::choices
>
object;

typedef
sge::sprite::parameters
<
	sprite_types::choices
>
parameters;

typedef
sge::sprite::state::all_choices
state_choices;

typedef
sge::sprite::state::object
<
	sprite_types::state_choices
>
state_object;

typedef
sge::sprite::state::parameters
<
	sprite_types::state_choices
>
state_parameters;

}

namespace particle
{
FCPPT_MAKE_STRONG_TYPEDEF(
	float_duration,
	life_time);

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector2,
	velocity);

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector2,
	acceleration);

FCPPT_MAKE_STRONG_TYPEDEF(
	unsigned,
	count);

class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		particle::life_time const &_life_time,
		sprite_types::parameters const &params,
		particle::velocity const &_velocity,
		particle::acceleration const &_acceleration)
	:
		life_timer_(
			sge::timer::parameters<sge::timer::clocks::standard>(
				_life_time.get())),
		seconds_timer_(
			sge::timer::parameters<sge::timer::clocks::standard>(
				float_duration(
					1.0f))),
		sprite_(
			params),
		color_(
			sprite_.color()),
		position_(
			sprite_.pos()),
		velocity_(
			_velocity),
		acceleration_(
			_acceleration)
	{
	}

	bool
	dead() const
	{
		return
			life_timer_.expired();
	}

	void
	update()
	{
		sge::renderer::scalar const delta =
			sge::timer::elapsed_fractional<sge::renderer::scalar>(
				seconds_timer_);

		seconds_timer_.reset();

		position_ +=
			delta * velocity_.get();
		velocity_ +=
			particle::velocity(
				delta * acceleration_.get());
		sprite_.pos(
			position_);
		sprite_.color(
			sge::timer::remaining_fractional<sge::renderer::scalar>(
				life_timer_) *
			color_);
	}

	sprite_types::object const &
	sprite() const
	{
		return
			sprite_;
	}
private:
	sge::timer::basic<sge::timer::clocks::standard> life_timer_;
	sge::timer::basic<sge::timer::clocks::standard> seconds_timer_;
	sprite_types::object sprite_;
	sprite_types::object::color_type color_;
	sge::renderer::vector2 position_;
	particle::velocity velocity_;
	particle::acceleration acceleration_;
};

class manager
{
FCPPT_NONCOPYABLE(
	manager);
public:
	manager(
		particle::count const &,
		sge::renderer::device::ffp &,
		sge::image2d::system &,
		sge::viewport::manager &);

	void
	update();

	void
	render(
		sge::renderer::context::ffp &);

	sge::renderer::vertex::declaration const &
	vertex_declaration() const;
private:
	typedef
	boost::ptr_list<particle::object>
	particle_sequence;

	typedef
	fcppt::random::generator::minstd_rand
	generator_type;

	typedef
	fcppt::random::distribution::basic
	<
		fcppt::random::distribution::parameters::uniform_real
		<
			float_duration::rep
		>
	>
	duration_distribution;

	typedef
	fcppt::random::distribution::basic
	<
		fcppt::random::distribution::parameters::uniform_real
		<
			sge::renderer::scalar
		>
	>
	scalar_distribution;

	typedef
	fcppt::random::variate
	<
		generator_type,
		duration_distribution
	>
	time_rng;

	typedef
	fcppt::random::variate
	<
		generator_type,
		scalar_distribution
	>
	scalar_rng;

	typedef
	std::vector<sprite_types::object>
	sprite_sequence;

	fcppt::signal::scoped_connection const viewport_connection_;
	particle::count const particle_count_;
	sprite_types::buffers_type sprite_buffers_;
	sprite_types::state_object sprite_states_;
	sprite_sequence sprites_;
	particle_sequence particles_;
	generator_type generator_;
	time_rng explosion_rng_;
	time_rng lifetime_rng_;
	scalar_rng velocity_radius_rng_;
	scalar_rng velocity_angle_rng_;
	fcppt::scoped_ptr<scalar_rng> position_x_rng_;
	fcppt::scoped_ptr<scalar_rng> position_y_rng_;
	scalar_rng size_rng_;
	scalar_rng color_rng_;
	sge::timer::basic<sge::timer::clocks::standard> explosion_timer_;
	sge::texture::const_part_scoped_ptr const texture_part_;

	void
	viewport_callback(
		sge::renderer::target::viewport const &);
};

particle::manager::manager(
	particle::count const &_particle_count,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_system,
	sge::viewport::manager &_viewport_manager
)
:
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&particle::manager::viewport_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	particle_count_(
		_particle_count
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::dynamic
	),
	sprite_states_(
		_renderer,
		sprite_types::state_parameters()
	),
	sprites_(),
	particles_(),
	generator_(
		fcppt::random::generator::seed_from_chrono
		<
			generator_type::seed
		>()
	),
	explosion_rng_(
		generator_,
		duration_distribution(
			duration_distribution::param_type(
				duration_distribution::param_type::min(
					0.5f
				),
				duration_distribution::param_type::sup(
					2.0f
				)
			)
		)
	),
	lifetime_rng_(
		generator_,
		duration_distribution(
			duration_distribution::param_type(
				duration_distribution::param_type::min(
					0.5f
				),
				duration_distribution::param_type::sup(
					2.f
				)
			)
		)
	),
	velocity_radius_rng_(
		generator_,
		scalar_distribution(
			scalar_distribution::param_type(
				scalar_distribution::param_type::min(
					0.f
				),
				scalar_distribution::param_type::sup(
					1000.f
				)
			)
		)
	),
	velocity_angle_rng_(
		generator_,
		scalar_distribution(
			scalar_distribution::param_type(
				scalar_distribution::param_type::min(
					0.f
				),
				scalar_distribution::param_type::sup(
					fcppt::math::twopi
					<
						sge::renderer::scalar
					>()
				)
			)
		)
	),
	position_x_rng_(),
	position_y_rng_(),
	size_rng_(
		generator_,
		scalar_distribution(
			scalar_distribution::param_type(
				scalar_distribution::param_type::min(
					10.f
				),
				scalar_distribution::param_type::sup(
					100.f
				)
			)
		)
	),
	color_rng_(
		generator_,
		scalar_distribution(
			scalar_distribution::param_type(
				scalar_distribution::param_type::min(
					0.f
				),
				scalar_distribution::param_type::sup(
					1.f
				)
			)
		)
	),
	explosion_timer_(
		sge::timer::parameters
		<
			sge::timer::clocks::standard
		>(
			float_duration(
				explosion_rng_()
			)
		)
		.active(
			false
		)
	),
	texture_part_(
		fcppt::make_unique_ptr
		<
			sge::texture::part_raw_ptr
		>(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("smooth_particle.png"),
				_renderer,
				_image_system,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::emulate_srgb::yes
			)
		)
	)
{
}

void
particle::manager::update()
{
	if(!explosion_timer_.active() || explosion_timer_.expired())
	{
		explosion_timer_.active(
			true);

		explosion_timer_.interval(
			float_duration(
				explosion_rng_()));
		explosion_timer_.reset();

		sprite_types::object::vector center(
			static_cast<sprite_types::object::vector::value_type>(
				(*position_x_rng_)()),
			static_cast<sprite_types::object::vector::value_type>(
				(*position_y_rng_)()));

		for (particle::count i(0u); i < particle_count_; ++i)
		{
			sge::renderer::scalar const
				radius =
					velocity_radius_rng_(),
				angle =
					velocity_angle_rng_();

			particle::velocity const vel(
				sge::renderer::vector2(
					radius * std::cos(angle),
					radius * std::sin(angle)));

			fcppt::container::ptr::push_back_unique_ptr(
				particles_,
				fcppt::make_unique_ptr<particle::object>(
					particle::life_time(
						float_duration(
							lifetime_rng_())),
					sprite_types::parameters()
						.pos(
							center)
						.point_size(
							static_cast<sprite_types::object::vector::value_type>(
								size_rng_()))
						.texture(
							sprite_types::object::texture_type(
								*texture_part_))
						.color(
							sge::image::color::rgba8
							(
								(sge::image::color::init::red() %= color_rng_())
								(sge::image::color::init::green() %= color_rng_())
								(sge::image::color::init::blue() %= color_rng_())
								(sge::image::color::init::alpha() %= 1.))),
					vel,
					particle::acceleration(
						-(static_cast<sge::renderer::scalar>(0.5) * vel.get()) + sge::renderer::vector2(0.0f,200.0f))));
		}
	}

	sprites_.clear();
	for(particle_sequence::iterator i = particles_.begin(); i != particles_.end();)
	{
		sprites_.push_back(
			i->sprite());
		i->update();
		if (i->dead())
			i =
				particles_.erase(
					i);
		else
			i++;
	}
}

void
particle::manager::render(
	sge::renderer::context::ffp &_render_context)
{
	sge::sprite::process::all(
		_render_context,
		sge::sprite::geometry::make_random_access_range(
			sprites_
		),
		sprite_buffers_,
		sge::sprite::compare::nothing(),
		sprite_states_);
}

sge::renderer::vertex::declaration const &
particle::manager::vertex_declaration() const
{
	return
		sprite_buffers_.parameters().vertex_declaration();
}

void
particle::manager::viewport_callback(
	sge::renderer::target::viewport const &_viewport
)
{
	position_x_rng_.take(
		fcppt::make_unique_ptr<
			scalar_rng
		>(
			generator_,
			scalar_distribution(
				scalar_distribution::param_type(
					scalar_distribution::param_type::min(
						0.f
					),
					scalar_distribution::param_type::sup(
						fcppt::cast::int_to_float<
							sge::renderer::scalar
						>(
							_viewport.get().w()
						)
					)
				)
			)
		)
	);

	position_y_rng_.take(
		fcppt::make_unique_ptr<
			scalar_rng
		>(
			generator_,
			scalar_distribution(
				scalar_distribution::param_type(
					scalar_distribution::param_type::min(
						0.f
					),
					scalar_distribution::param_type::sup(
						fcppt::cast::int_to_float<
							sge::renderer::scalar
						>(
							_viewport.get().h()
						)
					)
				)
			)
		)
	);
}

}
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context)
try
{
	particle::count::value_type particle_count;

	boost::program_options::options_description allowed_options_description("Allowed options");
	allowed_options_description.add_options()
		(
			"help",
			"produce help message")
		(
			"particle-count",
			boost::program_options::value<particle::count::value_type>(&particle_count)->required(),
			"Number of particles to spawn");

	boost::program_options::variables_map compiled_options;
	boost::program_options::store(
		boost::program_options::parse_command_line(
			_context.argc(),
			_context.argv(),
			allowed_options_description),
		compiled_options);

	if(compiled_options.count("help"))
	{
		std::cout << allowed_options_description << "\n";
		return
			awl::main::exit_success();
	}

	boost::program_options::notify(
		compiled_options);

	typedef
	sge::systems::instance
	<
		boost::mpl::vector4
		<
			sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
			sge::systems::with_window,
			sge::systems::with_input
			<
				boost::mpl::vector1
				<
					sge::systems::keyboard_collector
				>
			>,
			sge::systems::with_image2d
		>
	>
	systems_instance;

	systems_instance const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge point sprite test")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
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
					sge::log::location(),
					fcppt::log::level::debug
				)
			)
		)
	);

	particle::manager particle_system(
		particle::count(
			particle_count),
		sys.renderer_ffp(),
		sys.image_system(),
		sys.viewport_manager());

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::shader::context shader_context(
		sys.renderer_core());

	sge::shader::pair shader(
		shader_context,
		particle_system.vertex_declaration(),
		sge::shader::vertex_program_path(
			sge::config::media_path()
			/
			FCPPT_TEXT("shaders")
			/
			FCPPT_TEXT("point_sprite.cg")
		),
		sge::shader::pixel_program_path(
			sge::config::media_path()
			/
			FCPPT_TEXT("shaders")
			/
			FCPPT_TEXT("point_sprite.cg")
		),
		sge::shader::optional_cflags()
	);

	typedef
	sge::shader::parameter::matrix
	<
		sge::renderer::scalar,
		4,
		4
	>
	matrix;

	matrix const mpv_parameter(
		shader.vertex_program(),
		sge::shader::parameter::name(
			"mvp_matrix"
		),
		sys.renderer_core(),
		sge::shader::parameter::is_projection_matrix(
			true
		),
		matrix::matrix_type::identity()
	);

	/*
	sge::shader::parameter::planar_texture input_texture_parameter(
		shader.pixel_program(),
		sge::shader::parameter::name(
			"input_texture"
		),
		shader,
		sys.renderer_core()
	);*/

	while(
		sys.window_system().poll())
	{
		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		/*
		sge::renderer::state::scoped const scoped_state(
			scoped_block.get(),
			sge::renderer::state::list(
				sge::renderer::state::bool_::enable_point_sprite = true
			)
		);*/

		/*
		sge::renderer::glsl::uniform::variable_scoped_ptr const tex_var(
			program->uniform("tex"));

		sge::renderer::glsl::uniform::single_value(
			*tex_var,
			0
		);*/

		particle_system.update();

		particle_system.render(
			scoped_block.get());
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
