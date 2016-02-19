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


#include <sge/evdev/focus_manager.hpp>
#include <sge/window/object.hpp>
#include <awl/window/has_focus.hpp>
#include <awl/window/event/focus_in_callback.hpp>
#include <awl/window/event/focus_in_fwd.hpp>
#include <awl/window/event/focus_out_callback.hpp>
#include <awl/window/event/focus_out_fwd.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::evdev::focus_manager::focus_manager(
	awl::system::object &_system,
	sge::window::object const &_window
)
:
	focus_(
		awl::window::has_focus(
			_system,
			_window.awl_object()
		)
	),
	focus_in_connection_(
		_window.awl_window_event_processor().focus_in_callback(
			awl::window::event::focus_in_callback(
				std::bind(
					&sge::evdev::focus_manager::on_focus_in,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	focus_out_connection_(
		_window.awl_window_event_processor().focus_out_callback(
			awl::window::event::focus_out_callback(
				std::bind(
					&sge::evdev::focus_manager::on_focus_out,
					this,
					std::placeholders::_1
				)
			)
		)
	)
{
}

sge::evdev::focus_manager::~focus_manager()
{
}

bool
sge::evdev::focus_manager::focus() const
{
	return
		focus_;
}

void
sge::evdev::focus_manager::on_focus_in(
	awl::window::event::focus_in const &
)
{
	focus_ = true;
}

void
sge::evdev::focus_manager::on_focus_out(
	awl::window::event::focus_out const &
)
{
	focus_ = false;
}
