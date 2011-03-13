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

sge::systems::wrapped_window::wrapped_window(
	awl::system::object_shared_ptr const _system,
	awl::window::instance_shared_ptr const _window
)
:
	system_(_system),
	window_(_window)
{
}

awl::system::object_shared_ptr const
sge::systems::wrapped_window::system() const
{
	return system_;
}

awl::window::instance_shared_ptr const
sge::systems::wrapped_window::window() const
{
	return window_;
}
