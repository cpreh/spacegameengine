#include <sge/cegui/system.hpp>
#include <sge/cegui/logger.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/image/colors.hpp>
#include <sge/config/media_path.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/systems/viewport/fill_on_resize.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/unit.hpp>
#include <sge/extension_set.hpp>
#include <sge/window/instance.hpp>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/elements/CEGUIFrameWindow.h>
#include <CEGUI/elements/CEGUIEditbox.h>
#include <fcppt/text.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/duration.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/from_std_string.hpp>
#include <boost/foreach.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <cstdlib>

int main(
	int,
	char *[])
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	/* Usually too verbose (maybe add a log switcher later?)
	sgegui::log_context().apply(
		fcppt::log::location(
			FCPPT_TEXT("sgegui")) + FCPPT_TEXT("cegui"),
		std::tr1::bind(
			&fcppt::log::object::activate,
			std::tr1::placeholders::_1,
			fcppt::log::level::debug));
	*/

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::window(
			sge::window::simple_parameters(
				FCPPT_TEXT("simple gui test"),
				sge::window::dim(1024,768))))
		(sge::systems::renderer(
			sge::renderer::parameters(
				sge::renderer::visual_depth::depth32,
				sge::renderer::depth_stencil_buffer::d24,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling),
			sge::systems::viewport::fill_on_resize()))
		(sge::systems::parameterless::charconv)
			(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<sge::extension_set>(
					FCPPT_TEXT("png"))))
		(sge::systems::input(
			sge::systems::input_helper_field(
				sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
			sge::systems::cursor_option_field(
				sge::systems::cursor_option::confine) | sge::systems::cursor_option::hide))); 

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::cegui::system guisys(
		sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("TaharezLook.scheme"),
		sys.renderer(),
		sys.image_loader(),
		sys.charconv_system(),
		sys,
		*sys.keyboard_collector(),
		*sys.mouse_collector());

	sge::time::timer frame_timer(
		sge::time::second(
			static_cast<sge::time::unit>(
				1)));

	sge::cegui::toolbox::scoped_layout scoped_layout(
		sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("text_demo.layout"),
		sys.charconv_system());

	while (running)
	{
		sys.window()->dispatch();

		guisys.update(
			fcppt::chrono::duration_cast<sge::time::duration>(
				sge::time::second_f(
					frame_timer.reset())));

		sge::renderer::state::scoped scoped_state(
			sys.renderer(),
			sge::renderer::state::list
				(sge::renderer::state::bool_::clear_backbuffer = true)
				(sge::renderer::state::color::clear_color = sge::image::colors::red()));

		sge::renderer::scoped_block scoped_block(
			sys.renderer());

		guisys.render();
	}
}
catch (fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("fcppt::exception caught: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "std::exception caught: " << e.what() << "\n";
	return EXIT_FAILURE;
}
