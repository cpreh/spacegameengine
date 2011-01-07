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


#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/colors.hpp>
#include <sge/all_extensions.hpp>
#include <sge/config/media_path.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/no_program.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/dont_sort.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
//#include <sge/renderer/scoped_texture.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_unspecified_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/window/instance.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/time/duration.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/funit.hpp>
#include <sge/time/second_f.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/random/make_last_exclusive_range.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/text.hpp>
#include <mizuiro/color/operators/scalar_multiply.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>

namespace
{
typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sge::image::color::rgba8_format
	>,
	boost::mpl::vector3<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_unspecified_dim
	>
> sprite_choices;

typedef sge::sprite::system<
	sprite_choices
>::type sprite_system;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

typedef sge::sprite::parameters<
	sprite_choices
> sprite_parameters;

class particle
{
public:
	explicit
	particle(
		sge::time::duration const &_life_time,
		sprite_parameters const &params,
		sge::renderer::vector2 const &_velocity,
		sge::renderer::vector2 const &_acceleration)
	:
		life_timer_(
			_life_time),
		seconds_timer_(
			sge::time::second_f(
				static_cast<sge::time::funit>(
					1))),
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
	dead() 
	{
		return life_timer_.expired();
	}

	void
	update()
	{
		sge::renderer::scalar const delta = 
			static_cast<sge::renderer::scalar>(
				seconds_timer_.reset());
		position_ += 
			delta * velocity_;
		velocity_ += 
			delta * acceleration_;
		sprite_.pos(
			fcppt::math::vector::structure_cast<sprite_object::point>(
				position_));
		sprite_.color(
			(static_cast<sge::time::funit>(1) - life_timer_.elapsed_frames()) * color_);
	}

	sprite_object const &
	sprite() const
	{
		return sprite_;
	}
private:
	sge::time::timer life_timer_;
	sge::time::timer seconds_timer_;
	sprite_object sprite_;
	sprite_object::color_type color_;
	sge::renderer::vector2 position_;
	sge::renderer::vector2 velocity_;
	sge::renderer::vector2 acceleration_;
};

class particles
{
public:
	explicit
	particles(
		unsigned particle_count,
		sge::systems::instance const &);

	void
	update();

	void
	render();
private:
	typedef
	boost::ptr_list<particle>
	particle_sequence;

	typedef
	fcppt::random::uniform<sge::time::funit>
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
	sge::time::timer explosion_timer_;
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
			static_cast<sge::time::funit>(
				0.5),
			static_cast<sge::time::funit>(
				2.0))),
	lifetime_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::time::funit>(
				0.5),
			static_cast<sge::time::funit>(
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
				sys.renderer()->screen_size().w()))),
	position_y_rng_(
		fcppt::random::make_inclusive_range(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				sys.renderer()->screen_size().h()))),
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
		sge::time::second_f(
			explosion_rng_()),
		sge::time::activation_state::inactive),
	texture_(
		sge::texture::part_ptr(
			new sge::texture::part_raw(
				sys.renderer()->create_texture(
					sys.image_loader().load(
						sge::config::media_path() 
							/ FCPPT_TEXT("smooth_particle.png"))->view(),
					sge::renderer::filter::linear,
					sge::renderer::resource_flags::none))))
{
}

void
particles::update()
{
	if (!explosion_timer_.active() || explosion_timer_.expired())
	{
		if (!explosion_timer_.active())
			explosion_timer_.activate();

		explosion_timer_.interval(
			sge::time::second_f(
				explosion_rng_()));
		explosion_timer_.reset();

		sprite_object::point center(
			static_cast<sprite_object::point::value_type>(
				position_x_rng_()),
			static_cast<sprite_object::point::value_type>(
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

			particles_.push_back(
				new particle(
					sge::time::second_f(
						lifetime_rng_()),
					sprite_parameters()
						.pos(
							center)
						.point_size(
							static_cast<sprite_object::point::value_type>(
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
		fcppt::log::level::debug
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge animtest")
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						sge::renderer::screen_size(
							1024,
							768
						),
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
				),
				sge::systems::cursor_grab::off
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions
			)
		)
	);

	/*
	sge::renderer::scoped_texture scoped_tex(
		sys.renderer(),
		point_tex);
	*/

	fcppt::io::cifstream fragment_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("pointsprite_fragment.glsl"));

	fcppt::io::cifstream vertex_stream(
		sge::config::media_path()
		/ FCPPT_TEXT("shaders")
		/ FCPPT_TEXT("pointsprite_vertex.glsl"));

	sge::renderer::glsl::program_ptr const p(
		sys.renderer()->create_glsl_program(
			sge::renderer::glsl::istream_ref(
				vertex_stream),
			sge::renderer::glsl::istream_ref(
				fragment_stream)));

	sys.renderer()->glsl_program(
		p);

	sge::renderer::glsl::uniform::variable_ptr const v(
		p->uniform("tex"));

	sge::renderer::glsl::uniform::single_value(
		v,
		static_cast<int>(0));

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_point_sprites = true)
			(sge::renderer::state::bool_::enable_alpha_blending = true)
			(sge::renderer::state::bool_::clear_backbuffer = true) 
			(sge::renderer::state::color::clear_color = sge::image::color::rgba8
					(
						(sge::image::color::init::red %= 0.)
						(sge::image::color::init::green %= 0.)
						(sge::image::color::init::blue %= 0.)
						(sge::image::color::init::alpha %= 1.)
					))
			(sge::renderer::state::source_blend_func::src_alpha)
			(sge::renderer::state::dest_blend_func::inv_src_alpha)
		);

	/*
	sprite_system ss(
		sys.renderer()
	);
	*/

#if 0
	typedef std::vector<
		sprite_object
	> sprite_vector;

	sprite_vector sprites;

	for(
		int i = 0;
		i < 1;
		++i
	)
		sprites.push_back(
			sprite_object(
				sprite_parameters()
				.pos(
					sprite_object::point(
						100,
						200 + i
					)
				)
				.point_size(
					100
				)
				.texture(
					sge::texture::part_ptr(
						new sge::texture::part_raw(
							point_tex)))
				.color(
					sge::image::color::rgba8
					(
						(sge::image::color::init::red %= 1.)
						(sge::image::color::init::green %= 0.)
						(sge::image::color::init::blue %= 0.)
						(sge::image::color::init::alpha %= 1.)
					)
				)
				.elements()
			)
		);
#endif

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	particles ps(
		boost::lexical_cast<unsigned>(
			argv[1]),
		sys);

	while(
		running
	)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		ps.update();
		ps.render();

		/*
		ss.render(
			sprites.begin(),
			sprites.end(),
			sge::sprite::dont_sort(),
			sge::sprite::default_equal()
		);
		*/
	}

}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
