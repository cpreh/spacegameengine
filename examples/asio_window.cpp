#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/dim_type.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

#include <sge/x11/window.hpp>
#include <sge/x11/window_ptr.hpp>
#include <sge/x11/display.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/system/error_code.hpp>

#include <X11/Xlibint.h>

#include <iostream>
#include <ostream>

namespace
{

class test
{
	FCPPT_NONCOPYABLE(test)
public:
	test()
	:
		sys(
			sge::systems::list()
			(
				sge::window::parameters(
					FCPPT_TEXT("sge animtest"),
					sge::window::dim_type(
						1024,
						768
					)
				)
			)
			(
				sge::systems::parameterless::input
			)
		),
		io_service(),
		stream_wrapper(
			io_service,
			fcppt::dynamic_pointer_cast<
				sge::x11::window
			>(
				sys.window()
			)
			->display()
			->get()
			->fd
		),
		running(true),
		input_connection(
			sys.input_system()->register_callback(
				sge::input::action(
					sge::input::kc::key_escape,
					boost::phoenix::ref(running) = false
				)
			)
		)
	{
		{
		sge::x11::window_ptr const ptr(
			fcppt::dynamic_pointer_cast<
				sge::x11::window
			>(
				sys.window()
			)
		);
		
		ptr->map_raised();

		ptr->display()->sync();

		}
		std::cout << "ctor: " << sys.window().use_count() << '\n';

	}

	void
	start()
	{
		register_handlers();

		io_service.run();

		std::cout << "Running set to false\n";
	}

	void
	run(
		boost::system::error_code const &error
	)
	{
		if(
			error
		)
		{
			std::cout << "Error in socket\n";

			return;
		}

		sys.window()->dispatch();

		sys.input_system()->dispatch();

		if(
			!running
		)
			io_service.stop();
		else
			register_handlers();

	}
private:
	void
	register_handlers()
	{
		stream_wrapper.async_read_some(
			boost::asio::null_buffers(),
			std::tr1::bind(
				&test::run,
				this,
				std::tr1::placeholders::_1
			)
		);
	}

	sge::systems::instance const sys;

	boost::asio::io_service io_service;

	boost::asio::posix::stream_descriptor stream_wrapper;

	bool running;

	fcppt::signal::scoped_connection const input_connection;
};

}

int main()
try
{
	{
		test t;

		t.start();
	}
}
SGE_MAINLOOP_CATCH_BLOCK
