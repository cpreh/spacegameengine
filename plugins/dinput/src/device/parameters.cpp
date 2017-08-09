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


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>


sge::dinput::device::parameters::parameters(
	IDirectInput8 &_instance,
	GUID const _guid,
	sge::window::object &_sge_window,
	awl::backends::windows::window::object &_window,
	awl::backends::windows::system::event::handle &_event_handle
)
:
	instance_{
		_instance
	},
	guid_{
		_guid
	},
	sge_window_{
		_sge_window
	},
	window_{
		_window
	},
	event_handle_{
		_event_handle
	}
{
}

IDirectInput8 &
sge::dinput::device::parameters::instance() const
{
	return
		instance_;
}

GUID
sge::dinput::device::parameters::guid() const
{
	return
		guid_;
}

sge::window::object &
sge::dinput::device::parameters::sge_window() const
{
	return
		sge_window_;
}

awl::backends::windows::window::object &
sge::dinput::device::parameters::window() const
{
	return
		window_;
}

awl::backends::windows::system::event::handle &
sge::dinput::device::parameters::event_handle() const
{
	return
		event_handle_;
}
