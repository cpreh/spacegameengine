//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/opcode.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/system.hpp>
#include <sge/x11input/xi_opcode.hpp>
#include <sge/x11input/xi_version.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::x11input::system::system(
	fcppt::log::context_reference const _log_context
)
:
	sge::input::system(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("x11input")
			}
		)
	}
{
}

sge::x11input::system::~system()
= default;

sge::input::processor_unique_ptr
sge::x11input::system::create_processor(
	sge::window::object_ref const _window
)
{
	awl::backends::x11::window::object const &x11_window(
		fcppt::optional::to_exception(
			fcppt::cast::dynamic<
				awl::backends::x11::window::object const
			>(
				_window.get().awl_object()
			),
			[]{
				return
					sge::input::exception{
						FCPPT_TEXT("Window passed to x11input::system is not an X11 window.")
					};
			}
		).get()
	);

	sge::x11input::opcode const opcode(
		fcppt::optional::to_exception(
			sge::x11input::xi_opcode(
				x11_window.display().get()
			),
			[]{
				return
					sge::input::exception{
						FCPPT_TEXT("X Input extension not available!")
					};
			}
		)
	);

	// The first supported version we ask for and that is supported will be used
	if(
		!sge::x11input::xi_version(
			x11_window.display().get(),
			2,
			1
		)
	)
	{
		throw
			sge::input::exception{
				FCPPT_TEXT("The X server doesn't support XI2.1!")
			};
	}

	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::x11input::processor
			>(
				fcppt::make_ref(
					log_
				),
				_window,
				opcode
			)
		);
}

sge::input::capabilities_field
sge::x11input::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::cursor,
			sge::input::capabilities::focus,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse
		};
}
