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
#include <sge/mainloop/io_service.hpp>
#include <sge/mainloop/asio/create_io_service.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

int main()
try
{
	sge::mainloop::io_service_ptr const io_service(
		sge::mainloop::asio::create_io_service()
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge asio test")
			)
			.dim(
				sge::window::dim_type(
					1024,
					768
				)
			)
			.io_service(
				io_service
			)
		)
		(
			sge::systems::parameterless::input
		)
	);

	sys.window()->show();

	fcppt::signal::scoped_connection const input_connection(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				std::tr1::bind(
					&sge::mainloop::io_service::stop,
					io_service
				)
			)
		)
	);

	io_service->run();
}
SGE_MAINLOOP_CATCH_BLOCK
