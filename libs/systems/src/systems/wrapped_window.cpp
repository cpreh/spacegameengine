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


#include <sge/systems/wrapped_window.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>


sge::systems::wrapped_window::wrapped_window(
	awl::system::object &_awl_system,
	awl::window::object &_awl_window
)
:
	awl_system_(
		_awl_system
	),
	awl_window_(
		_awl_window
	)
{
}

awl::system::object &
sge::systems::wrapped_window::awl_system() const
{
	return
		awl_system_;
}

awl::window::object &
sge::systems::wrapped_window::awl_window() const
{
	return
		awl_window_;
}
