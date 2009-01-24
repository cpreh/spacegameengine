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
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/skins/standard.hpp>

#include <sge/log/headers.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/font/drawer.hpp>
#include <sge/font/system.hpp>
#include <sge/font/font.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>
#include <sge/make_shared_ptr.hpp>

#include <iostream>

namespace
{
struct end_program
{
	end_program(bool &running) : running(running) {}
	void operator()() const { running = false; }
	bool &running;
};

struct show_data
{
	show_data(
		bool &_running,
		sge::gui::widgets::edit const &_hostname,
		sge::gui::widgets::edit const &_port) 
			: running(_running),
			  hostname(_hostname),
				port(_port) {}

	void operator()() const 
	{
		running = false; 
		sge::cerr << SGE_TEXT("game would now connect to ") 
		          << hostname.text() << SGE_TEXT(" on port ") 
							<< port.text() << SGE_TEXT("\n");
	}

	bool &running;
	sge::gui::widgets::edit const &hostname,&port;
};

class input_functor
{
	public:
	explicit input_functor(
		bool &running,
		sge::gui::widget &_top)
		: running(running),
		  top_(_top)
	{
	}

	void operator()(sge::input::key_pair const &k) const
	{
		if (k.key().code() == sge::input::kc::key_f1 && k.value())
			top_.activation(
				top_.activation() == sge::gui::activation_state::active
					? sge::gui::activation_state::inactive
					: sge::gui::activation_state::active);
		if (k.key().code() == sge::input::kc::key_escape)
			running = false;
	}
	private:
	bool &running;
	sge::gui::widget &top_;
};

class connect_functor
{
	public:
	connect_functor(
		sge::gui::widget &_connect_menu,
		sge::gui::widget &_main_menu)
		: connect_menu_(_connect_menu),
		  main_menu_(_main_menu)
		{}
	
	void connect_to_server()
	{
		main_menu_.activation(sge::gui::activation_state::inactive);
		connect_menu_.activation(sge::gui::activation_state::active);
	}

	void return_to_menu()
	{
		connect_menu_.activation(sge::gui::activation_state::inactive);
		main_menu_.activation(sge::gui::activation_state::active);
	}
	private:
		sge::gui::widget &connect_menu_;
		sge::gui::widget &main_menu_;
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
	
	sge::gui::widget top(
		(sge::gui::widget::parent_data(m)));
	top.pos(sge::gui::point(100,100));
	top.size(sge::gui::dim(500,300));
	top.layout(sge::make_shared_ptr<sge::gui::layouts::vertical>(boost::ref(top)));
	top.activation(sge::gui::activation_state::inactive);

	sge::gui::widget host(
		(sge::gui::widget::parent_data(top)));
	host.layout(sge::make_shared_ptr<sge::gui::layouts::horizontal>(boost::ref(host)));

	sge::gui::widgets::label host_label(
		(sge::gui::widget::parent_data(host)),
		SGE_TEXT("Hostname:"));
	sge::gui::widgets::edit host_edit(
		(sge::gui::widget::parent_data(host)),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(30,1));

	sge::gui::widget port(
		(sge::gui::widget::parent_data(top)));
	port.layout(sge::make_shared_ptr<sge::gui::layouts::horizontal>(boost::ref(port)));

	sge::gui::widgets::label port_label(
		(sge::gui::widget::parent_data(port)),
		SGE_TEXT("Port:"));
	sge::gui::widgets::edit port_edit(
		(sge::gui::widget::parent_data(port)),
		sge::gui::widgets::edit::single_line,
		sge::gui::dim(5,1));
	
	sge::gui::widgets::button connect(
		(sge::gui::widget::parent_data(top)),
		SGE_TEXT("Connect"));

	sge::gui::widgets::button return_menu(
		(sge::gui::widget::parent_data(top)),
		SGE_TEXT("Return"));

	
	sge::gui::widget main_menu(
		(sge::gui::widget::parent_data(m)));
	main_menu.pos(sge::gui::point(100,100));
	main_menu.size(sge::gui::dim(300,400));
	main_menu.layout(
		sge::make_shared_ptr<sge::gui::layouts::vertical>(
			boost::ref(main_menu)));
	
	sge::gui::widgets::button menu_connect(
		(sge::gui::widget::parent_data(main_menu)),
		SGE_TEXT("Connect to server"));
	
	connect_functor cf(
		top,
		main_menu);

	sge::gui::widgets::button menu_start(
		(sge::gui::widget::parent_data(main_menu)),
		SGE_TEXT("Start server"));

	sge::gui::widgets::button menu_exit(
		(sge::gui::widget::parent_data(main_menu)),
		SGE_TEXT("Exit"));
	
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
		sys.input_system()->register_callback(
			input_functor(
				running,
				top));

	sge::signals::connection mc0 = menu_connect.clicked.connect(
		boost::bind(&connect_functor::connect_to_server,&cf));

	sge::signals::connection mc1 = return_menu.clicked.connect(
		boost::bind(&connect_functor::return_to_menu,&cf));

	sge::signals::connection mc2 = connect.clicked.connect(
		show_data(
			running,
			host_edit,
			port_edit));
	
	sge::signals::connection mc3 = 
		menu_exit.clicked.connect(
			p);
	
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
