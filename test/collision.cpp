/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/time/timer.hpp>
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/shapes/circle.hpp>
#include <sge/collision/shapes/circle.hpp>
#include <sge/collision/group.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <fcppt/math/vector/output.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/dont_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/window/parameters.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/satellite.hpp>
#include <sge/collision/world.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/exception.hpp>
#include <sge/optional_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <exception>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <functional>

namespace
{

typedef sge::image::color::rgba8_format sprite_color;

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector1<
		sge::sprite::with_color
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

void collision_begin(
	sge::collision::satellite &,
	sge::collision::satellite &)
{
	std::cerr << "collision begin!\n";
}

void collision_end(
	sge::collision::satellite &,
	sge::collision::satellite &)
{
	std::cerr << "collision end!\n";
}

bool test_callback0(
	sge::collision::satellite const &,
	sge::collision::satellite const &)
{
	//sge::cerr << "test callback called\n";
	return true;
}

bool test_callback1(
	sge::collision::satellite const &,
	sge::collision::satellite const &)
{
	//sge::cerr << "test callback called\n";
	return false;
}

class object : public sge::collision::satellite
{
public:
	explicit object(
		sprite_object &sprite_
	)
	:
		sprite_(sprite_)
	{
	}

	void position_change(sge::collision::point const &p)
	{
		typedef sprite_object::unit unit;

		sprite_.x(
			static_cast<
				unit
			>(
				p.x()
			)
		);

		sprite_.y(
			static_cast<
				unit
			>(
				p.y()
			)
		);
	}
private:
	sprite_object &sprite_;
};
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge physics")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						640,
						480
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			)
		)
		(sge::systems::parameterless::collision_system)
		(sge::systems::parameterless::input)
	);

	sge::collision::world_ptr const world(
		sys.collision_system()->create_world(
			sge::collision::rect(
				sge::collision::rect::pos_type(
					-10,
					-10
				),
				sge::collision::rect::dim_type(
					660,
					500
				)
			)
		)
	);

	world->test_callback_combiner(std::logical_or<bool>());

	fcppt::signal::auto_connection
		bc = world->register_begin_callback(&collision_begin),
		be = world->register_end_callback(&collision_end),
		foobar0 = world->register_test_callback(&test_callback0),
		foobar1 = world->register_test_callback(&test_callback1);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_object s_a(
		sprite_parameters()
		.pos(
			sprite_object::point(600,0)
		)
		.size(
			sprite_object::dim(10,10)
		)
		.color(
			sge::image::color::any::convert<
				sprite_color
			>(
				sge::image::colors::white()
			)
		)
		.elements()
	);

	sprite_object s_b(
		sprite_parameters()
		.pos(
			sprite_object::point(10,0)
		)
		.size(
			sprite_object::dim(10,10)
		)
		.color(
			sge::image::color::any::convert<
				sprite_color
			>(
				sge::image::colors::white()
			)
		)
		.elements()
	);

	sge::collision::body_ptr const body_a(
		world->create_body(
			sge::collision::satellite_ptr(
				new object(s_a)
			),
			sge::assign::make_container<
				sge::collision::shapes::container
			>(
				world->create_circle(
					static_cast<sge::collision::unit>(100)
				)
			),
			sge::collision::point(
				static_cast<sge::collision::unit>(320),
				static_cast<sge::collision::unit>(240),
				static_cast<sge::collision::unit>(0)
			),
			sge::collision::point(
				static_cast<sge::collision::unit>(0),
				static_cast<sge::collision::unit>(0),
				static_cast<sge::collision::unit>(0)
			)
		)
	);


	sge::collision::body_ptr const body_b(
		world->create_body(
			sge::collision::satellite_ptr(
				new object(s_b)
			),
			sge::assign::make_container<
				sge::collision::shapes::container
			>(
				world->create_circle(
					static_cast<sge::collision::unit>(5)
				)
			),
			sge::collision::point(
				static_cast<sge::collision::unit>(320),
				static_cast<sge::collision::unit>(240),
				static_cast<sge::collision::unit>(0)
			),
			sge::collision::point(
				static_cast<sge::collision::unit>(0),
				static_cast<sge::collision::unit>(0),
				static_cast<sge::collision::unit>(0)
			)
		)
	);

	sge::cerr << "velocity is " << body_a->linear_velocity() << "\n";

	sge::collision::group_ptr const
		g_a = world->create_group(),
		g_b = world->create_group();

	world->collides_with(
		g_a,
		g_a
	);

	world->collides_with(
		g_a,
		g_b
	);

	g_a->add(
		body_a);
	g_a->add(
		body_b);

	sprite_system ss(
		sys.renderer()
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
		);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::time::timer frame_timer(sge::time::second(1));
	sge::time::timer vel_timer(sge::time::second(5));

	while (running)
	{
		world->update(
			frame_timer.elapsed_frames()
		);

		frame_timer.reset();

		sge::time::sleep(
			sge::time::second_f(
				1.0f/60.0f
			)
		);

		if (vel_timer.expired())
		{
			body_b->linear_velocity(
				sge::collision::point(
					static_cast<sge::collision::unit>(100),
					static_cast<sge::collision::unit>(0),
					static_cast<sge::collision::unit>(0)
				)
			);
		}

		sge::mainloop::dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		typedef std::vector<
			sprite_object
		> sprite_container;

		sprite_container sprites;

		sprites.push_back(s_a);
		sprites.push_back(s_b);

		ss.render(
			sprites.begin(),
			sprites.end(),
			sge::sprite::dont_sort(),
			sge::sprite::default_equal()
		);
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
