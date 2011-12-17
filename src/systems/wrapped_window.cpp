/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/wrapped_window.hpp>
#include <awl/event/processor_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/window/instance_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>


sge::systems::wrapped_window::wrapped_window(
	awl::system::object &_awl_system,
	awl::system::event::processor &_awl_system_event_processor,
	awl::event::processor &_awl_event_processor,
	awl::window::instance &_awl_window,
	awl::window::event::processor &_awl_window_event_processor
)
:
	awl_system_(
		_awl_system
	),
	awl_system_event_processor_(
		_awl_system_event_processor
	),
	awl_event_processor_(
		_awl_event_processor
	),
	awl_window_(
		_awl_window
	),
	awl_window_event_processor_(
		_awl_window_event_processor
	)
{
}

awl::system::object &
sge::systems::wrapped_window::awl_system() const
{
	return awl_system_;
}

awl::system::event::processor &
sge::systems::wrapped_window::awl_system_event_processor() const
{
	return awl_system_event_processor_;
}

awl::event::processor &
sge::systems::wrapped_window::awl_event_processor() const
{
	return awl_event_processor_;
}

awl::window::instance &
sge::systems::wrapped_window::awl_window() const
{
	return awl_window_;
}

awl::window::event::processor &
sge::systems::wrapped_window::awl_window_event_processor() const
{
	return awl_window_event_processor_;
}
