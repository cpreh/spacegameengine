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


/**
 	Example descripton:

	This example demonstrates a simple use case of the stencil buffer.
	Suppose you have a smaller sprite and a bigger sprite.
	The smaller sprite is rendered first and the bigger sprite is
	rendered second. Because the bigger sprite completely overlaps
	the smaller sprite, only the bigger sprite would be visible under
	normal circumstances.
	However, in this example, the stencil buffer is initialized to
	all 0s on each frame. When the smaller sprite is rendered,
	the stencil buffer is incremented to 1 for every pixel that
	the smaller sprite coveres. When the bigger sprite is rendered,
	the stencil test then compares to the reference value 0,
	not touching the area in which the smaller sprite was rendered.
	Thus we create a "hole" in the bigger sprite, leading to the
	same effect as if the two sprites were rendered in reverse order.
*/

#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
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
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
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
#include <sge/systems/image2d.hpp>
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
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	// The desired window size.
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			// Request a window with the desired size.
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge stencil example")
					),
					window_dim
				)
			)
		)
		(
			// Request a depth and stencil buffer (d24s8).
			// We don't use the depth buffer, but to be most portable,
			// d24s8 is the only sensible choice.
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24s8,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				// Put the viewport in the center of the window
				// when the window is bigger than the desired size.
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			// Request a keyboard collector which acts as if
			// all the connected keyboards were a sinlge keyboard.
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				// Nothing special to do with the cursor.
				sge::systems::cursor_option_field()
			)
		)
		(
			// Request an image loader that can load png files.
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
				)
			)
		)
	);

	// Declare which sprites we want.
	// The sprite should use int as its position and size,
	// float as its depth, rotation, etc (which we don't use),
	// and no color.
	// Also request that the sprite has a dimension
	// (meaning it is a rectangle and consists of two triangles)
	// and that the sprite needs textures.
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

	// Declare the sprite system type, object type and parameters type.
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

	// This is our smaller sprite.
	// It will be placed at position (200, 200) and have the size
	// of its texture "grass.png" which is (256, 256).
	sprite_object small_sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				200,
				200
			)
		)
		.texture(
			// Sprite uses an abstraction of textures
			// (which is texture::part) that can refer to
			// a part of a physical texture.
			// We don't want that here, so we use part_raw which
			// coveres the whole texture.
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				// Create a texture from "grass.png",
				// which uses no mipmapping
				// and clamping at its corners.
				sge::renderer::texture::create_planar_from_path(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("grass.png"),
					sys.renderer(),
					sys.image_system(),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			)
		)
		// The sprite will get the texture's size.
		.texture_size()
	);

	// This is our bigger sprite.
	// It will be placed at position (0, 0) and have the size
	// of its texture "cloudsquare.png" which is (512, 512).
	// Everything else is pretty much the same to small_sprite.
	sprite_object big_sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				sge::renderer::texture::create_planar_from_path(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("cloudsquare.png"),
					sys.renderer(),
					sys.image_system(),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::clamp
					),
					sge::renderer::resource_flags::none
				)
			)
		)
		.texture_size()
	);

	// Declare which states should be always active.
	// Here, we clear the back buffer with the clear color black() on each frame.
	// We also clear the stencil buffer with value 0.
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

	// Set running to false when escape is pressed.
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
		// Process window messages which will also process input.
		sys.window_system().poll();

		// Declare a render block.
		// This will clear the buffers in the constructor and
		// present the scene in the destructor.
		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		{
			// Set the stencil buffer to always pass and increment
			// the value stored in the stencil buffer for every pixel rendered.
			// Because the stencil buffer has been cleared to 0,
			// every entry in the stencill buffer will be 1 where
			// small_sprite is rendered.
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

			// Render small sprite.
			sge::sprite::render_one(
				sprite_sys,
				small_sprite
			);
		}

		{
			// Set the stencil buffer to pass when its value is still 0,
			// which means it passes everywhere where small_sprite
			// has _not_ been rendered.
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

			// Render big sprite.
			sge::sprite::render_one(
				sprite_sys,
				big_sprite
			);
		}
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
