/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/all_extensions.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/glsl/const_optional_program.hpp>
#include <sge/renderer/glsl/create_program.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/program_parameters.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
//#include <sge/renderer/scoped_texture.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/dont_sort.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_unspecified_dim.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/timer/remaining_fractional.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/chrono/duration.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/lexical_cast.hpp>
#include <mizuiro/color/operators/scalar_multiply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <vector>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

namespace
{
sge::window::dim window_dim(1024,768);

typedef
fcppt::chrono::duration<sge::renderer::scalar>
float_duration;

typedef
sge::sprite::choices
<
	sge::sprite::type_choices
	<
		int,
		float,
		sge::image::color::rgba8_format
	>,
	boost::mpl::vector3
	<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_unspecified_dim
	>
>
sprite_choices;

typedef
sge::sprite::system
<
	sprite_choices
>::type
sprite_system;

typedef
sge::sprite::object
<
	sprite_choices
>
sprite_object;

typedef
sge::sprite::parameters
<
	sprite_choices
>
sprite_parameters;

class particle
{
FCPPT_NONCOPYABLE(
	particle);
public:
	explicit
	particle(
		float_duration const &_life_time,
		sprite_parameters const &params,
		sge::renderer::vector2 const &_velocity,
		sge::renderer::vector2 const &_acceleration)
	:
		life_timer_(
			sge::timer::parameters<sge::timer::clocks::standard>(
				_life_time)),
		seconds_timer_(
			sge::timer::parameters<sge::timer::clocks::standard>(
				float_duration(
					1.0f))),
		sprite_(
			params.elements()),
		color_(
			sprite_.color()),
		position_(
			fcppt::math::vector::structure_cast<sge::renderer::vector2>(
				sprite_.pos())),
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
			delta * velocity_;
		velocity_ +=
			delta * acceleration_;
		sprite_.pos(
			fcppt::math::vector::structure_cast<sprite_object::vector>(
				position_));
		sprite_.color(
			sge::timer::remaining_fractional<sge::renderer::scalar>(life_timer_) * color_);
	}

	sprite_object const &
	sprite() const
	{
		return sprite_;
	}
private:
	sge::timer::basic<sge::timer::clocks::standard> life_timer_;
	sge::timer::basic<sge::timer::clocks::standard> seconds_timer_;
	sprite_object sprite_;
	sprite_object::color_type color_;
	sge::renderer::vector2 position_;
	sge::renderer::vector2 velocity_;
	sge::renderer::vector2 acceleration_;
};

class particles
{
FCPPT_NONCOPYABLE(
	particles);
public:
	explicit
	particles(
		unsigned particle_count,
		sge::systems::instance const &);

	void
	update();

	void
	render();

	sge::renderer::vertex_declaration const &
	vertex_declaration() const;
private:
	typedef
	boost::ptr_list<particle>
	particle_sequence;

	typedef
	fcppt::random::uniform<float_duration::rep>
	time_rng;

	typedef
	fcppt::random::uniform<sge::renderer::scalar>
	scalar_rng;

	typedef
	std::vector<sprite_object>
	sprite_sequence;

	unsigned const particle_count_;
	sprite_system ss_;
	sprite_sequence sprites_;
	particle_sequence particles_;
	time_rng explosion_rng_;
	time_rng lifetime_rng_;
	scalar_rng velocity_radius_rng_;
	scalar_rng velocity_angle_rng_;
	scalar_rng position_x_rng_;
	scalar_rng position_y_rng_;
	scalar_rng size_rng_;
	scalar_rng color_rng_;
	sge::timer::basic<sge::timer::clocks::standard> explosion_timer_;
	sge::texture::part_ptr texture_;
};

particles::particles(
	unsigned const _particle_count,
	sge::systems::instance const &sys)
:
	particle_count_(
		_particle_count),
	ss_(
		sys.renderer()),
	particles_(),
	explosion_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<float_duration::rep>(
				0.5),
			static_cast<float_duration::rep>(
				2.0))),
	lifetime_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<float_duration::rep>(
				0.5),
			static_cast<float_duration::rep>(
				2.0))),
	velocity_radius_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				1000))),
	velocity_angle_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			fcppt::math::twopi<sge::renderer::scalar>())),
	position_x_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				window_dim.w()))),
	position_y_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				window_dim.h()))),
	size_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				10),
			static_cast<sge::renderer::scalar>(
				100))),
	color_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				1))),
	explosion_timer_(
		sge::timer::parameters<sge::timer::clocks::standard>(
			float_duration(
				explosion_rng_()))
				.active(
					false)),
	texture_(
		fcppt::make_shared_ptr<sge::texture::part_raw>(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("smooth_particle.png"),
				sys.renderer(),
				sys.image_loader(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none)))
{
}

void
particles::update()
{
	if(!explosion_timer_.active() || explosion_timer_.expired())
	{
		explosion_timer_.active(
			true);

		explosion_timer_.interval(
			float_duration(
				explosion_rng_()));
		explosion_timer_.reset();

		sprite_object::vector center(
			static_cast<sprite_object::vector::value_type>(
				position_x_rng_()),
			static_cast<sprite_object::vector::value_type>(
				position_y_rng_()));

		for (unsigned i = 0; i < particle_count_; ++i)
		{
			sge::renderer::scalar const
				radius =
					velocity_radius_rng_(),
				angle =
					velocity_angle_rng_();

			sge::renderer::vector2 const vel(
				radius * std::cos(angle),
				radius * std::sin(angle));

			fcppt::container::ptr::push_back_unique_ptr(
				particles_,
				fcppt::make_unique_ptr<particle>(
					float_duration(
						lifetime_rng_()),
					sprite_parameters()
						.pos(
							center)
						.point_size(
							static_cast<sprite_object::vector::value_type>(
								size_rng_()))
						.texture(
							texture_)
						.color(
							sge::image::color::rgba8
							(
								(sge::image::color::init::red %= color_rng_())
								(sge::image::color::init::green %= color_rng_())
								(sge::image::color::init::blue %= color_rng_())
								(sge::image::color::init::alpha %= 1.))),
					vel,
					-(static_cast<sge::renderer::scalar>(0.5) * vel) + sge::renderer::vector2(0,200)));
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
particles::render()
{
	ss_.render(
		sprites_.begin(),
		sprites_.end(),
		sge::sprite::dont_sort(),
		sge::sprite::default_equal());
}

sge::renderer::vertex_declaration const &
particles::vertex_declaration() const
{
	return ss_.vertex_declaration();
}
}

int main(
	int argc,
	char *argv[])
try
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <particle-count>\n";
		return EXIT_FAILURE;
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge point sprite example"),
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
					sge::systems::input_helper::keyboard_collector),
				sge::systems::cursor_option_field::null()))
		(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions)));

	particles ps(
		fcppt::lexical_cast<unsigned>(
			std::string(
				argv[1])),
		sys);

	fcppt::io::cifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("pointsprite")
		/ FCPPT_TEXT("fragment.glsl"));

	fcppt::io::cifstream vertex_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("pointsprite")
		/ FCPPT_TEXT("vertex.glsl"));

	sge::renderer::glsl::program_ptr const program(
		sge::renderer::glsl::create_program(
			sys.renderer(),
			sge::renderer::glsl::program_parameters()
				.vertex_shader(
					ps.vertex_declaration(),
					std::string(
						std::istreambuf_iterator<char>(
							vertex_stream),
						std::istreambuf_iterator<char>()))
				.pixel_shader(
					std::string(
						std::istreambuf_iterator<char>(
							fragment_stream),
						std::istreambuf_iterator<char>()))));

	sys.renderer().glsl_program(
		*program);

	sge::renderer::glsl::uniform::variable_ptr const v(
		program->uniform("tex"));

	sge::renderer::glsl::uniform::single_value(
		*v,
		static_cast<int>(0));

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	while(
		running)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer());

		ps.update();
		ps.render();
	}
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
