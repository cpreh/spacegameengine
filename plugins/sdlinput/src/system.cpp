//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/sdlinput/processor.hpp>
#include <sge/sdlinput/system.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL.h>
#include <fcppt/config/external_end.hpp>


sge::sdlinput::system::system(
	fcppt::log::context_reference const _log_context
)
:
	sge::input::system{},
	init_{
		SDL_INIT_JOYSTICK
	},
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("sdlinput")
			}
		)
	}
{
}

sge::sdlinput::system::~system()
{
}

sge::input::processor_unique_ptr
sge::sdlinput::system::create_processor(
	sge::window::object_ref const _window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::sdlinput::processor
			>(
				_window,
				fcppt::make_ref(
					this->log_
				)
			)
		);
}

sge::input::capabilities_field
sge::sdlinput::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::cursor,
			sge::input::capabilities::focus,
			sge::input::capabilities::joypad,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse
		};
}
