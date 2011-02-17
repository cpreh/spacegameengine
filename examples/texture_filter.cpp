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


#include <sge/camera/activation_state.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/perspective.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/stencil_buffer.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/window_mode.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

int 
main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge texture filter example")
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
					sge::renderer::depth_buffer::d24,
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
				)
				| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::confine
				)
				| sge::systems::cursor_option::hide
			)
		)
	);

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::projection::perspective(
				sge::renderer::aspect(
					sys.renderer()->screen_size()
				),
				// fov
				fcppt::math::deg_to_rad(
					static_cast<
						sge::renderer::scalar
					>(
						90
					)
				),
				// near
				static_cast<
					sge::renderer::scalar
				>(
					0.1
				),
				// far
				static_cast<
					sge::renderer::scalar
				>(
					10
				)
			),
			// movementspeed
			static_cast<
				sge::renderer::scalar
			>(
				0.2
			),
			// mousespeed
			static_cast<
				sge::renderer::scalar
			>(
				200.0
			),
			// position
			sge::camera::identity_gizmo(),
			*sys.keyboard_collector(),
			*sys.mouse_collector(),
			sge::camera::activation_state::active
		)
	);

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector3<
			sge::sprite::with_dim,
			sge::sprite::with_texture,
			sge::sprite::with_repetition
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

	sprite_system sprite_sys(
		sys.renderer()
	);

	sprite_object sprite(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.size(
			sprite_object::dim(
				1000u,
				1000u
			)
		)
		.repetition(
			100u
		)
		.texture(
			sge::texture::const_part_ptr()
		) // TODO!
		.elements()
	);

	bool running(
		true
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	sge::time::timer frame_timer(
		sge::time::second(
			1
		)
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(
				sge::renderer::state::color::clear_color
					= sge::image::colors::lightblue()
			)
	);

	while(
		running
	)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		camera.update(
			static_cast<
				sge::renderer::scalar
			>(
				frame_timer.reset()
			)
		);

		sys.renderer()->transform(
			sge::renderer::matrix_mode::world,
			camera.world()
		);

		sys.renderer()->transform(
			sge::renderer::matrix_mode::projection,
			camera.projection()
		);

		sge::sprite::render_one(
			sprite_sys,
			sprite
		);
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
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
