#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/scoped.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/headers.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/iostream.hpp>
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

	sge::renderer::screen_size_t const screen_size(640,480);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge gui test")))
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
	
	sge::gui::widgets::edit b(
		(sge::gui::widget::parent_data(m)),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,30));
	b.pos(sge::gui::point(10,10));
	b.size(sge::gui::dim(400,300));
	//b.text(SGE_TEXT("test"));

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
	
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());
		m.draw();
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
	return EXIT_FAILURE;
}
