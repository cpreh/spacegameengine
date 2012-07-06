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


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/log/global.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/location.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/charconv.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <set>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	// Usually too verbose (maybe add a log switcher later?)
	sge::log::global_context().apply(
		fcppt::log::location(
			sge::log::location()
			/
			FCPPT_TEXT("cegui")),
		std::tr1::bind(
			&fcppt::log::object::activate,
			std::tr1::placeholders::_1,
			fcppt::log::level::debug));

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
			sge::window::parameters(
				sge::window::title(
					FCPPT_TEXT("simple gui test")),
				sge::window::dim(1024,768))))
		(sge::systems::renderer(
			sge::renderer::parameters(
				sge::renderer::windowed(
					sge::renderer::bit_depth::depth32),
				sge::renderer::depth_stencil_buffer::d24,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling),
			sge::viewport::fill_on_resize()))
		(sge::systems::charconv())
			(sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("png"))))))
		(sge::systems::input(
			sge::systems::input_helper_field(
				sge::systems::input_helper::keyboard_collector)
				| sge::systems::input_helper::mouse_collector
				| sge::systems::input_helper::cursor_demuxer,
			sge::systems::cursor_option_field())));

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::cegui::system gui_sys(
		sge::cegui::load_context(
			sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("TaharezLook.scheme"))
			.font_directory(
				sge::config::media_path()/FCPPT_TEXT("fonts")),
		sys.renderer(),
		sys.image_system(),
		sys.charconv_system(),
		sys.viewport_manager(),
		sge::cegui::cursor_visibility::visible);

	sge::cegui::syringe gui_syringe(
		gui_sys);

	sge::cegui::default_cursor gui_cursor(
		gui_syringe,
		sys.cursor_demuxer());

	sge::cegui::default_keyboard gui_keyboard(
		gui_syringe,
		sys.keyboard_collector());

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::cegui::duration(
				static_cast<sge::cegui::unit>(
					1))));

	sge::cegui::toolbox::scoped_layout scoped_layout(
		gui_sys,
		sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("text_demo.layout"));

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet(
		gui_sys,
		scoped_layout.window()
	);

	while(
		sys.window_system().poll())
	{
		gui_sys.update(
			sge::timer::elapsed<sge::cegui::duration>(
				frame_timer));

		frame_timer.reset();

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::red()
			)
		);

		gui_sys.render(
			scoped_block.get()
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
