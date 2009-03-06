#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/button.hpp>
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
#include <sge/signals/scoped_connection.hpp>
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

#define TL_SINGLE_BUTTON 0
#define TL_MULTIPLE_BUTTONS 1
#define TL_CHILD_CONTAINERS 2
#define TL_REMOVE_WIDGETS 3

#define TESTING_LEVEL TL_REMOVE_WIDGETS

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size_t const screen_size(640,480);

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
		sge::gui::skin_ptr(new sge::gui::skins::standard()));
	
#if TESTING_LEVEL == TL_SINGLE_BUTTON
	sge::gui::widgets::button b((sge::gui::widget::parent_data(m)),SGE_TEXT("Button A"));
	b.relative_pos(sge::gui::point(10,10));
	b.size(sge::gui::dim(400,300));
#elif TESTING_LEVEL == TL_MULTIPLE_BUTTONS
	sge::gui::widget top((sge::gui::widget::parent_data(m)));
	top.layout(sge::make_shared_ptr<sge::gui::layouts::horizontal>(boost::ref(top)));
	top.relative_pos(sge::gui::point(10,10));
	top.size(sge::gui::dim(400,300));

	sge::gui::widgets::button left((sge::gui::widget::parent_data(top)),SGE_TEXT("Button A"));
	sge::gui::widgets::button right((sge::gui::widget::parent_data(top)),SGE_TEXT("Button B"));
#elif TESTING_LEVEL == TL_CHILD_CONTAINERS || TESTING_LEVEL == TL_REMOVE_WIDGETS
	sge::gui::widget top((sge::gui::widget::parent_data(m)));
	top.layout(sge::make_shared_ptr<sge::gui::layouts::horizontal>(boost::ref(top)));
	top.relative_pos(sge::gui::point(10,10));
	top.size(sge::gui::dim(400,300));

	sge::cerr << "added top level widget\n";

	sge::gui::widget left((sge::gui::widget::parent_data(top)));
	left.layout(sge::make_shared_ptr<sge::gui::layouts::vertical>(boost::ref(left)));

	sge::gui::widget right((sge::gui::widget::parent_data(top)));
	right.layout(sge::make_shared_ptr<sge::gui::layouts::vertical>(boost::ref(right)));

	sge::gui::widgets::button left_top(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left top) me!"));
	
	sge::gui::widgets::button left_bottom(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left bottom) me!"));

	sge::shared_ptr<sge::gui::widgets::button>
		right_top(new sge::gui::widgets::button(
			sge::gui::widget::parent_data(right),
			SGE_TEXT("(right top) me!")));

	sge::gui::widgets::button right_bottom(
		sge::gui::widget::parent_data(right),
		SGE_TEXT("(right bottom) me!"));

	sge::cerr << "added buttons and children\n";
#else
#error "invalid testing level"
#endif

	// set sensible render states
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = 
				sge::renderer::rgba8_color(0, 0, 0, 255))
			(sge::renderer::state::cull_mode::off)
		);
	
	bool running = true;
	end_program p(running);
	sge::signals::scoped_connection const conn =
		sys.input_system()->register_callback(input_functor(running));
	
#if TESTING_LEVEL == TL_SINGLE_BUTTON
	b.clicked.connect(p);
#elif TESTING_LEVEL == TL_MULTIPLE_BUTTONS
	left.clicked.connect(p);
#elif TESTING_LEVEL == TL_CHILD_CONTAINERS || TESTING_LEVEL == TL_REMOVE_WIDGETS
	left_top.clicked.connect(p);
#endif
	sge::cerr << SGE_TEXT("---------------------------\nall widgets added!\n");
	
#if TESTING_LEVEL == TL_REMOVE_WIDGETS
	sge::time::timer delete_timer(sge::time::second(static_cast<sge::time::unit>(2)));
#endif
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());

#if TESTING_LEVEL == TL_REMOVE_WIDGETS
		if (delete_timer.active() && delete_timer.expired())
		{
			sge::cerr << SGE_TEXT("sge: gui test program: removing button\n");
			delete_timer.deactivate();
			right_top.reset();
		}
#endif

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
