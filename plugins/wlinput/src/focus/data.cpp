//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/timer/object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::wlinput::focus::data::data(
	fcppt::log::object &_log,
	sge::wlinput::focus::object &_focus,
	sge::wlinput::xkb_context const &_xkb_context,
	awl::system::event::processor &_processor,
	awl::backends::wayland::window::object const &_window,
	awl::event::container_reference const _events
)
:
	log_{
		_log
	},
	focus_{
		_focus
	},
	xkb_context_{
		_xkb_context
	},
	processor_{
		_processor
	},
	window_{
		_window
	},
	events_{
		_events
	},
	entered_{
		false
	},
	xkb_keymap_{},
	xkb_state_{},
	last_pressed_{},
	repeat_timer_{}
{
}

sge::wlinput::focus::data::~data()
{
}
