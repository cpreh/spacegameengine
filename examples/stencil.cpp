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


#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/create_texture.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <exception>
#include <iostream>
#include <cstdlib>

int
main()
try
{

	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge stencil example"),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24s8,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field()
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
	);

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector2<
			sge::sprite::with_dim,
			sge::sprite::with_texture
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

	sprite_object sprite1(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				200,
				200
			)
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				sge::image2d::create_texture(
					sge::config::media_path()
					/ FCPPT_TEXT("grass.png"),
					sys.renderer(),
					sys.image_loader(),
					sge::renderer::texture::filter::linear,
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			)
		)
		.texture_size()
		.elements()
	);

	sprite_object sprite2(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				sge::image2d::create_texture(
					sge::config::media_path()
					/ FCPPT_TEXT("cloudsquare.png"),
					sys.renderer(),
					sys.image_loader(),
					sge::renderer::texture::filter::linear,
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			)
		)
		.texture_size()
		.elements()
	);

	sys.renderer().state(
		sge::renderer::state::list
		(
			sge::renderer::state::bool_::clear_back_buffer = true
		)
		(
			sge::renderer::state::bool_::clear_stencil_buffer = true
		)
		(
			sge::renderer::state::color::back_buffer_clear_color
				= sge::image::colors::black()
		)
		(
			sge::renderer::state::int_::stencil_buffer_clear_val = 0
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const escape_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		{
			sge::renderer::state::scoped const scoped_state(
				sys.renderer(),
				sge::renderer::state::list
				(
					sge::renderer::state::stencil_func::always
				)
				(
					sge::renderer::state::stencil_op::pass =
						sge::renderer::state::stencil_op_value::inc_sat
				)
			);

			sge::sprite::render_one(
				sprite_sys,
				sprite1
			);
		}

		{
			sge::renderer::state::scoped const scoped_state(
				sys.renderer(),
				sge::renderer::state::list
				(
					sge::renderer::state::int_::stencil_ref = 0
				)
				(
					sge::renderer::state::stencil_func::equal
				)
			);

			sge::sprite::render_one(
				sprite_sys,
				sprite2
			);
		}
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
