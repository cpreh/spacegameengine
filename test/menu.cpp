#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
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

#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/log/headers.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/funit.hpp>
#include <sge/font/system.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/structure_cast.hpp>

#include <iostream>
#include <ostream>
#include <exception>

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
		sge::cerr
			<< SGE_TEXT("game would now connect to ") 
			<< hostname.text() << SGE_TEXT(" on port ") 
			<< port.text() << SGE_TEXT('\n');
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
	:
		connect_menu_(_connect_menu),
		main_menu_(_main_menu),
		pos_connect(
			static_cast<sge::time::funit>(50),
			static_cast<sge::time::funit>(50)),
		vantage_connect(
			static_cast<sge::time::funit>(-2000),
			static_cast<sge::time::funit>(200)),
		pos_main(
			static_cast<sge::time::funit>(50),
			static_cast<sge::time::funit>(50)),
		vantage_main(
			static_cast<sge::time::funit>(200),
			static_cast<sge::time::funit>(-2000)),
		real_main(time_vector::null()),
		real_connect(time_vector::null()),
		speed(static_cast<sge::time::funit>(10))
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

	void update(sge::time::funit const delta)
	{
		if (connect_menu_.activation() == sge::gui::activation_state::active)
		{
			real_main += speed * delta * (vantage_main - real_main);
			real_connect += speed * delta * (pos_connect - real_connect);
		}
		else
		{
			real_main += speed * delta * (pos_main - real_main);
			real_connect += speed * delta * (vantage_connect - real_connect);
		}
		main_menu_.pos(sge::structure_cast<sge::gui::point>(real_main));
		connect_menu_.pos(sge::structure_cast<sge::gui::point>(real_connect));
	}
	private:
	typedef sge::math::vector::static_<sge::time::funit,2>::type time_vector;

	sge::gui::widget &connect_menu_;
	sge::gui::widget &main_menu_;
	time_vector pos_connect;
	time_vector vantage_connect;
	time_vector pos_main;
	time_vector vantage_main;
	time_vector real_main;
	time_vector real_connect;
	sge::time::funit speed;
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

	top.activation(sge::gui::activation_state::inactive);

	sge::time::timer frame_timer(sge::time::second(1));
	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block block(sys.renderer());
		cf.update(frame_timer.elapsed_frames());
		frame_timer.reset();
		m.draw();
		m.invalidate(top.absolute_area());
		m.invalidate(main_menu.absolute_area());
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << '\n';
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
