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
#include <sge/systems/viewport/center_on_resize.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

int
main(
	int argc,
	char **argv
)
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
					FCPPT_TEXT("sge fonttest"),
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
				sge::systems::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::parameterless::font
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

	sge::font::metrics_ptr const metrics(
		sys.font_system()->create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(15)
		)
	);

	sge::font::text::drawer_3d drawer(
		sys.renderer(),
		sge::image::colors::green());

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

	sge::font::text::string const string(
		argc == 2
		?
			sge::font::text::from_fcppt_string(
				fcppt::from_std_string(
					argv[1]
				)
			)
		:
			SGE_FONT_TEXT_LIT("hello world 1234567890hello world 123456789hello world 123456789hello world 123456789000")
	);

	while(
		running
	)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block(sys.renderer());

		sge::font::text::draw(
			metrics,
			drawer,
			string,
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::font::rect::dim
				>(
					sys.renderer()->onscreen_target()->viewport().get().size()
				)
			),
			sge::font::text::align_h::center,
			sge::font::text::align_v::center,
			sge::font::text::flags::none
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
