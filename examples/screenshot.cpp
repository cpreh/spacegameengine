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
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/config/media_path.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <iostream>
#include <ostream>
#include <exception>
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
					FCPPT_TEXT("sge screenshot test"),
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
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
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

	sge::renderer::device &device(
		sys.renderer()
	);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					device
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp
				)
			)
		)
	);

	sge::texture::const_part_ptr const tex(
		sge::texture::add_image(
			tex_man,
			*sys.image_loader().load(
				sge::config::media_path() / FCPPT_TEXT("tux.png")
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
			sge::sprite::with_texture,
			sge::sprite::with_dim
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
		device
	);

	sprite_object bg(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.texture(
			tex
		)
		.texture_size()
		.elements()
	);

	device.state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color
				= sge::image::colors::green()
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

	fcppt::signal::scoped_connection const cb2(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::f12,
				std::tr1::bind(
					sge::renderer::screenshot,
					fcppt::ref(
						device
					),
					fcppt::ref(
						sys.image_loader()
					),
					fcppt::filesystem::path(
						FCPPT_TEXT("output.png")
					)
				)
			)
		)
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			device
		);

		sge::sprite::render_one(
			ss,
			bg
		);
	}
}
catch(
	std::exception const &_exception
)
{
	std::cerr << _exception.what() << '\n';

	return EXIT_FAILURE;
}
