//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/processor.hpp>
#include <sge/dinput/system.hpp>
#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>


sge::dinput::system::system(
	fcppt::log::context &_log_context
)
:
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("dinput")
			}
		)
	}
{
}

sge::dinput::system::~system()
{
}

sge::input::processor_unique_ptr
sge::dinput::system::create_processor(
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::dinput::processor
			>(
				log_,
				_window
			)
		);
}

sge::input::capabilities_field
sge::dinput::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse,
			sge::input::capabilities::joypad
		};
}
