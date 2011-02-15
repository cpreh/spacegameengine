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
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/font/bitmap/create.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/config/media_path.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/instance.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
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

	sge::font::metrics_ptr const font_metrics(
		sge::font::bitmap::create(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("bitmap")
			/ FCPPT_TEXT("font.png"),
			sys.image_loader()
		)
	);

	sge::font::text::drawer_3d font_drawer(
		sys.renderer(),
		sge::image::colors::white());

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color
				= sge::image::colors::black()
			)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	while(running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::font::text::draw(
			font_metrics,
			font_drawer,
			SGE_FONT_TEXT_LIT("test abcd"),
			sge::font::pos::null(),
			fcppt::math::dim::structure_cast<
				sge::font::dim
			>(
				sys.renderer()->screen_size()
			),
			sge::font::text::align_h::center,
			sge::font::text::align_v::center,
			sge::font::text::flags::none
		);
	}
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr << _exception.what() << '\n';

	return EXIT_FAILURE;
}
