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


#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/wrapped.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>


sge::systems::impl::window::wrapped::wrapped(
	sge::systems::wrapped_window const &_parameters,
	sge::window::system &_system
)
:
	sge::systems::impl::window::base(),
	window_(
		_system.create(
			_parameters.awl_window()
		)
	)
{
}

sge::systems::impl::window::wrapped::~wrapped()
{
}

sge::window::object &
sge::systems::impl::window::wrapped::get() const
{
	return
		*window_;
}
