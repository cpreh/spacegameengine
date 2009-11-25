/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/angle.hpp>

// TODO: do we have to check the contents here
// as not every (forward, up) pair is right

sge::audio::angle::angle()
:
	forward_(),
	up_()
{}

sge::audio::angle::angle(
	point const &forward_,
	point const &up_)
:
	forward_(forward_),
	up_(up_)
{}

sge::audio::point const &
sge::audio::angle::forward() const
{
	return forward_;
}

void
sge::audio::angle::forward(
	point const &nforward)
{
	forward_ = nforward;
}

sge::audio::point const
sge::audio::angle::up() const
{
	return up_;
}

void
sge::audio::angle::up(
	point const &nup)
{
	up_ = nup;
}
