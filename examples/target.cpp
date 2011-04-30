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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/config/media_path.hpp>
#include <sge/window/instance.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

int main()
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
				sge::window::simple_parameters(
					FCPPT_TEXT("sge targettest"),
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
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
			)
		)
	);

	sge::image2d::file_ptr const image(
		sys.image_loader().load(
			sge::config::media_path()
			/ FCPPT_TEXT("tux.png")
		)
	);

	sge::renderer::texture::planar_ptr const image_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer(),
			image->view(),
			sge::renderer::texture::filter::linear,
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::readable
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

	sprite_system ss(
		sys.renderer()
	);

	sge::renderer::texture::planar_ptr const target_texture(
		sys.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::renderer::dim2(
					640,
					480
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp
				),
				sge::renderer::resource_flags::readable, // TODO
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target
				)
			)
		)
	);

	sge::renderer::target_ptr const target(
		sge::renderer::target_from_texture(
			sys.renderer(),
			*target_texture
		)
	);

	sprite_object rendered_stuff(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				target_texture
			)
		)
		.texture_size()
		.elements()
	);

	{
		sys.renderer().state(
			sge::renderer::state::list
			(
				sge::renderer::state::bool_::clear_backbuffer = true
			)
			(
				sge::renderer::state::color::clear_color
					= sge::image::colors::red()
			)
		);

		sprite_object my_object(
			sprite_parameters()
			.pos(
				sprite_object::vector(
					100,
					0
				)
			)
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					image_texture
				)
			)
			.texture_size()
			.elements()
		);

		sprite_object my_object_2(
			sprite_parameters()
			.pos(
				sprite_object::vector(
					100,
					20
				)
			)
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					image_texture
				)
			)
			.texture_size()
			.elements()
		);

		sys.renderer().state(
			sge::renderer::state::list
			(
				sge::renderer::state::bool_::clear_backbuffer = true
			)
			(
				sge::renderer::state::color::clear_color
					= sge::image::colors::red()
			)
		);

		sys.renderer().texture(
			sge::renderer::no_texture(),
			sge::renderer::stage_type(
				0u
			)
		);

		sge::renderer::scoped_target const target_(
			sys.renderer(),
			*target
		);

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			my_object
		);

		sge::sprite::render_one(
			ss,
			my_object_2
		);
	}

	sys.renderer().state(
		sge::renderer::state::list
		(
			sge::renderer::state::bool_::clear_backbuffer = true
		)
		(
			sge::renderer::state::color::clear_color
				= sge::image::colors::blue()
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	while (running)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			rendered_stuff
		);
	}
}
catch (sge::exception const &e)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("caught sge exception: ")
		<< e.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr
		<< "caught std exception: "
		<< e.what()
		<< '\n';
	
	return EXIT_FAILURE;
}
