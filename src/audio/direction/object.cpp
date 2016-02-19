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


#include <sge/audio/vector.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/direction/up.hpp>


sge::audio::direction::object::object(
	sge::audio::direction::forward const &_forward,
	sge::audio::direction::up const &_up
)
:
	forward_(
		_forward.get()
	),
	up_(
		_up.get()
	)
{
}

sge::audio::vector
sge::audio::direction::object::forward() const
{
	return
		forward_;
}

void
sge::audio::direction::object::forward(
	sge::audio::vector const &_forward
)
{
	forward_ =
		_forward;
}

sge::audio::vector
sge::audio::direction::object::up() const
{
	return
		up_;
}

void
sge::audio::direction::object::up(
	sge::audio::vector const &_up
)
{
	up_ =
		_up;
}
