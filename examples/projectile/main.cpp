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


#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/log/global_context.hpp>
#include <sge/projectile/debug_drawer.hpp>
#include <sge/projectile/dim2.hpp>
#include <sge/projectile/duration.hpp>
#include <sge/projectile/log_location.hpp>
#include <sge/projectile/rect.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/static.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/scoped.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <sge/projectile/shape/circle.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
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
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/math/box/box.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename Container,typename Ch,typename Traits>
Container const
container_from_stream(
	std::basic_istream<Ch,Traits> &s)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
	{
		s.setstate(
			std::ios_base::failbit);
		return Container();
	}

	s >> c;
	Container result;
	while(c != s.widen(')'))
	{
		s.putback(
			c);
		if(!s)
			return Container();
		typename Container::value_type new_value;
		s >> new_value;
		if(!s)
			return Container();
		result.insert(
			result.end(),
			new_value);
		s >> c;
		s >> c;
	}

	return result;
}

class body
{
FCPPT_NONCOPYABLE(
	body);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	explicit
	body(
		sge::projectile::world &_world,
		sge::projectile::group::object &_group,
		sge::projectile::shape::shared_base_ptr const shape,
		sge::projectile::body::solidity::variant const &solidity,
		sge::projectile::rect const &r)
	:
		body_(
			sge::projectile::body::parameters(
				sge::projectile::body::position(
					fcppt::math::vector::structure_cast<sge::projectile::vector2>(
						fcppt::math::box::center(
							r))),
				sge::projectile::body::linear_velocity(
					sge::projectile::vector2::null()),
				sge::projectile::body::angular_velocity(
					static_cast<sge::projectile::scalar>(
						0)),
				shape,
				sge::projectile::body::rotation(
					static_cast<sge::projectile::scalar>(
						0)),
				solidity,
				sge::projectile::body::user_data())),
		body_scope_(
			_world,
			body_,
			fcppt::assign::make_container<sge::projectile::group::sequence>(
				fcppt::ref(
					_group)))
	{
	}
FCPPT_PP_POP_WARNING

	~body()
	{
	}

	sge::projectile::body::object &
	get()
	{
		return body_;
	}
private:
	sge::projectile::body::object body_;
	sge::projectile::body::scoped body_scope_;
};

class body_keyboard_mover
{
	FCPPT_NONCOPYABLE(
		body_keyboard_mover
	);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	explicit
	body_keyboard_mover(
		sge::projectile::world &_world,
		sge::projectile::body::object &_body,
		sge::input::keyboard::device &_keyboard)
	:
		body_(
			_body),
		body_collision_connection_(
			_world.body_collision(
				std::tr1::bind(
					&body_keyboard_mover::body_collision,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2))),
		key_callback_connection_(
			_keyboard.key_callback(
				std::tr1::bind(
					&body_keyboard_mover::key_callback,
					this,
					std::tr1::placeholders::_1))),
		velocity_(
			sge::projectile::vector2::null())
	{
	}
FCPPT_PP_POP_WARNING

	~body_keyboard_mover()
	{
	}
private:
	sge::projectile::body::object &body_;
	fcppt::signal::scoped_connection const body_collision_connection_;
	fcppt::signal::scoped_connection const key_callback_connection_;
	sge::projectile::vector2 velocity_;

	void
	body_collision(
		sge::projectile::body::object const &a,
		sge::projectile::body::object const &b)
	{
		if (&a == &body_ || &b == &body_)
		{
			body_.linear_velocity(
				velocity_);
			body_.angular_velocity(
				static_cast<sge::projectile::scalar>(
					0));
		}
	}

	void
	key_callback(
		sge::input::keyboard::key_event const &e)
	{
		velocity_ =
			body_.linear_velocity() +
				static_cast<sge::projectile::scalar>(30) *
				key_event_to_vector(
					e);
		body_.linear_velocity(
			velocity_);
	}

	sge::projectile::vector2 const
	key_event_to_vector(
		sge::input::keyboard::key_event const &e)
	{
		sge::projectile::vector2 result =
			sge::projectile::vector2::null();

		switch (e.key_code())
		{
			case sge::input::keyboard::key_code::left:
				result = sge::projectile::vector2(-1,0);
				break;
			case sge::input::keyboard::key_code::right:
				result = sge::projectile::vector2(1,0);
				break;
			case sge::input::keyboard::key_code::up:
				result = sge::projectile::vector2(0,-1);
				break;
			case sge::input::keyboard::key_code::down:
				result = sge::projectile::vector2(0,1);
				break;
			default:
				break;
		}

		return e.pressed() ? result : (-result);
	}

};

void
body_collision(
	sge::projectile::body::object const &,
	sge::projectile::body::object const &)
{
	static unsigned ticker = 1u;
	std::cout << ticker++ << ": body collision!\n";
}

class body_following_ghost
{
	FCPPT_NONCOPYABLE(
		body_following_ghost
	);
public:
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	explicit
	body_following_ghost(
		sge::projectile::world &_world,
		sge::projectile::body::object &_body,
		sge::projectile::ghost::size const &_size,
		sge::projectile::group::sequence const &_groups)
	:
		ghost_(
			sge::projectile::ghost::parameters(
				sge::projectile::ghost::position(
					_body.position()),
				_size)),
		ghost_scope_(
			_world,
			ghost_,
			_groups),
		body_position_change_connection_(
			_body.position_change(
				std::tr1::bind(
					&body_following_ghost::body_position_change,
					this,
					std::tr1::placeholders::_1))),
		body_enter_connection_(
			ghost_.body_enter(
				std::tr1::bind(
					&body_following_ghost::body_enter,
					this,
					std::tr1::placeholders::_1))),
		body_exit_connection_(
			ghost_.body_exit(
				std::tr1::bind(
					&body_following_ghost::body_exit,
					this,
					std::tr1::placeholders::_1)))
	{
	}
FCPPT_PP_POP_WARNING

	~body_following_ghost()
	{
	}
private:
	sge::projectile::ghost::object ghost_;
	sge::projectile::ghost::scoped ghost_scope_;
	fcppt::signal::scoped_connection const
		body_position_change_connection_,
		body_enter_connection_,
		body_exit_connection_;

	void
	body_position_change(
		sge::projectile::body::position const &p)
	{
		ghost_.position(
			p.get());
	}

	void
	body_enter(
		sge::projectile::body::object const &)
	{
		std::cout << "Body enter!\n";
	}

	void
	body_exit(
		sge::projectile::body::object const &)
	{
		std::cout << "Body exit!\n";
	}
};
}

int main()
try
{
	sge::log::global_context().apply(
		sge::projectile::log_location(),
		std::tr1::bind(
			&fcppt::log::activate_levels,
			std::tr1::placeholders::_1,
			fcppt::log::level::debug));

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("projectile")),
					sge::window::dim(1024,768))))
		(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::center_on_resize(
					sge::window::dim(1024,768))))
		(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector),
				sge::systems::cursor_option_field::null())));

	sge::projectile::world world;

	fcppt::signal::scoped_connection const body_collision_world(
		world.body_collision(
			&body_collision));

	sge::projectile::debug_drawer debug_drawer(
		world,
		sys.renderer());
	sge::projectile::group::object
		first_group(
			world),
		second_group(
			world);
	world.make_groups_collide(
		first_group,
		second_group);

	debug_drawer.active(
		true);

	body first_body(
		world,
		first_group,
		fcppt::make_shared_ptr<sge::projectile::shape::circle>(
			static_cast<sge::projectile::scalar>(
				5)),
		sge::projectile::body::solidity::solid(
			sge::projectile::body::mass(
				static_cast<sge::projectile::scalar>(
					1))),
		sge::projectile::rect(
			sge::projectile::vector2(
				10,10),
			sge::projectile::dim2(
				10,10)));

	std::istringstream polygon_stream(
		"((42,296),(253,162),(12,23),(420,22),(420,310))");

	body second_body(
		world,
		second_group,
		fcppt::make_shared_ptr<sge::projectile::shape::triangle_mesh>(
			sge::projectile::triangulation::triangulate<
				sge::projectile::triangulation::default_tag,
				sge::projectile::shape::triangle_sequence
			>(
				container_from_stream< std::vector< sge::projectile::vector2 > >(
					polygon_stream),
				static_cast<sge::projectile::scalar>(
					0.00001))),
		sge::projectile::body::solidity::static_(),
		sge::projectile::rect(
			sge::projectile::vector2(
				100,100),
			sge::projectile::dim2(
				20,20)));

	body_following_ghost first_ghost(
		world,
		first_body.get(),
		sge::projectile::ghost::size(
			sge::projectile::dim2(
				100,
				100)),
		fcppt::assign::make_container<sge::projectile::group::sequence>(
			fcppt::ref(
				first_group)));

	body_keyboard_mover keyboard_mover(
		world,
		first_body.get(),
		sys.keyboard_collector());

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

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::projectile::duration(
				1.0f)));

	while(running)
	{
		sys.window_system().poll();

		world.update_continuous(
			sge::projectile::time_increment(
				sge::timer::elapsed<sge::projectile::duration>(
					frame_timer)));

		frame_timer.reset();

		debug_drawer.update();

		sge::renderer::scoped_block const block_(
			sys.renderer());

		debug_drawer.render(
			sge::sprite::projection_matrix(
				sys.renderer().onscreen_target().viewport()));
	}
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
