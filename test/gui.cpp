#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/default_cursor.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/headers.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/font/system.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

namespace
{
struct end_program
{
	end_program(bool &running) : running(running) {}
	void operator()() const { running = false; }
	bool &running;
};

class input_functor
{
	public:
	explicit input_functor(bool &running)
		: running(running)
	{
	}

	void operator()(sge::input::key_pair const &k) const
	{
		if (k.key().code() == sge::input::kc::key_escape)
			running = false;
	}
	private:
	bool &running;
};
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge gui test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));

	
	sge::gui::manager m(
		sys.renderer(),
		sys.image_loader(),
		sys.input_system(),
		sys.font_system(),
		sge::gui::skin_ptr(
			new sge::gui::skins::standard()),
		sge::gui::cursor_ptr(
			new sge::gui::default_cursor(
				sys.image_loader(),
				sys.renderer())));
	
	sge::gui::widgets::backdrop top(
		sge::gui::widget::parent_data(m),
		sge::gui::widget::parameters()
			.pos(sge::gui::point(10,10))
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>()));
			/*
			.size(sge::gui::dim(400,300)));*/

	sge::cerr << "added top level widget\n";

	sge::gui::widget left(
		top,
		sge::gui::widget::parameters()
			.layout(sge::make_shared_ptr<sge::gui::layouts::vertical>()));

	sge::gui::widget right(
		top,
		sge::gui::widget::parameters()
			.layout(sge::make_shared_ptr<sge::gui::layouts::vertical>()));

	sge::gui::widgets::buttons::text left_top(
		left,
		sge::gui::widget::parameters(),
		SGE_TEXT("(left top) me!"));
	
	sge::gui::widgets::buttons::text left_bottom(
		left,
		sge::gui::widget::parameters(),
		SGE_TEXT("(left bottom) me!"));

	sge::shared_ptr<sge::gui::widgets::buttons::text>
		right_top(new sge::gui::widgets::buttons::text(
			right,
			sge::gui::widget::parameters(),
			SGE_TEXT("(right top) me!")));

	sge::gui::widgets::buttons::text right_bottom(
		right,
		sge::gui::widget::parameters(),
		SGE_TEXT("(right bottom) me!"));

	sge::cerr << "added buttons and children\n";

	// set sensible render states
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = 
				sge::renderer::rgba8_color(255, 0, 0, 255))
			(sge::renderer::state::cull_mode::off)
		);
	
	bool running = true;
	end_program p(running);
	sge::signal::scoped_connection const conn(
		sys.input_system()->register_callback(
			input_functor(
				running
			)
		)
	);
	
	sge::signal::scoped_connection const conn2(
		left_top.register_clicked(p)
	);
	sge::cerr << SGE_TEXT("---------------------------\nall widgets added!\n");
	
	sge::time::timer delete_timer(sge::time::second(static_cast<sge::time::unit>(2)));
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());

		if (delete_timer.active() && delete_timer.expired())
		{
			sge::cerr << SGE_TEXT("sge: gui test program: removing button\n");
			delete_timer.deactivate();
			right_top.reset();
		}

		m.update();
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
