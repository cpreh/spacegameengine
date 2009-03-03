#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/window/parameters.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/cerr.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge fullscreen test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					800,
					600),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::fullscreen)));
	
	sge::time::timer tm(
		sge::time::second(10));

	sge::renderer::device_ptr const rend(
		sys.renderer());

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::rgba8_color(255, 255, 0, 255)));

	while(!tm.update_b())
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(rend);
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
