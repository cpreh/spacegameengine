#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/font_drawer_canvas.hpp>

#include <sge/log/headers.hpp>
#include <sge/font/drawer.hpp>
#include <sge/font/system.hpp>
#include <sge/font/font.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>

#include <iostream>

namespace
{
struct end_program
{
	end_program(bool &running) : running(running) {}
	void operator()() const { running = false; }
	bool &running;
};
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size_t const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge gui test"),
			(sge::renderer::parameters(
				sge::renderer::display_mode(
					screen_size,
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed))))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));
	
	sge::gui::manager m(
		sys.renderer(),
		sys.image_loader(),
		sys.input_system(),
		sys.font_system());

	sge::gui::widgets::container top((sge::gui::widget::parent_data(m)));
	top.layout<sge::gui::layouts::horizontal>();
	top.pos(sge::gui::point(10,10));
	top.size_hint(sge::gui::dim(400,300));

	sge::gui::widgets::container left((sge::gui::widget::parent_data(top)));
	left.layout<sge::gui::layouts::vertical>();

	sge::gui::widgets::container right((sge::gui::widget::parent_data(top)));
	right.layout<sge::gui::layouts::vertical>();

	sge::gui::widgets::button left_top(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left top) me!"));
	
	sge::gui::widgets::button left_bottom(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left bottom) me!"));

	sge::gui::widgets::button right_top(
		sge::gui::widget::parent_data(right),
		SGE_TEXT("(right top) me!"));

	sge::gui::widgets::button right_bottom(
		sge::gui::widget::parent_data(right),
		SGE_TEXT("(right bottom) me!"));
	
	// compile the stuff!
	top.compile();

	// set sensible render states
	sys.renderer()->set_state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = 
				sge::renderer::rgba8_color(0, 0, 0, 255))
			(sge::renderer::state::cull_mode::off)
		);
	
	bool running = true;
	end_program p(running);
	left_top.clicked.connect(p);
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());
		m.draw();
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
