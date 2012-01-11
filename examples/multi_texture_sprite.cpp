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


#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
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
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_arg.hpp>
#include <sge/renderer/texture/stage_arg_value.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/render/one.hpp>
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
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge multi texture sprite example")
					),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>
					(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
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
	);

	sge::renderer::texture::planar_ptr const texture1(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("color_map.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none
		)
	);

	sge::renderer::texture::planar_ptr const texture2(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none
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
					2u
				>,
				sge::sprite::config::texture_coordinates::normal
			>
		>
	> sprite_choices;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::system<
		sprite_choices
	> sprite_system;

	sprite_system sprite_sys(
		sys.renderer(),
		sge::sprite::buffers_option::dynamic
	);

	sprite_object const sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture_level<0>(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				texture1
			)
		)
		.texture_level<1>(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				texture2
			)
		)
		.texture_size()
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
		sys.window_system().poll();

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::texture
		);

		sys.renderer().texture_stage_op(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::arg0
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::previous
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color1,
			sge::renderer::texture::stage_arg_value::texture
		);

		sys.renderer().texture_stage_op(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::modulate
		);

		sge::sprite::render::one(
			sprite,
			sprite_sys.buffers()
		);
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
