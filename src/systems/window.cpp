/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>


sge::systems::window::window(
	sge::systems::window_source const &_source
)
:
	source_(
		_source
	),
	show_(
		true
	),
	quit_(
		true
	)
{
}

sge::systems::window &
sge::systems::window::dont_show()
{
	show_ =
		false;

	return
		*this;
}

sge::systems::window &
sge::systems::window::dont_quit()
{
	quit_ =
		false;

	return
		*this;
}

sge::systems::window_source const &
sge::systems::window::source() const
{
	return
		source_;
}

bool
sge::systems::window::show() const
{
	return
		show_;
}

bool
sge::systems::window::quit() const
{
	return
		quit_;
}
