/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
