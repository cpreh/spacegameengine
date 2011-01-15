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


#include "../listener.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sge::audio_null::listener::listener()
:
	position_(
		audio::vector::null()
	),
	linear_velocity_(
		audio::vector::null()
	),
	direction_()
{}

sge::audio::vector const
sge::audio_null::listener::position() const
{
	return position_;
}

void
sge::audio_null::listener::position(
	audio::vector const &p)
{
	position_ = p;
}

sge::audio::vector const
sge::audio_null::listener::linear_velocity() const
{
	return linear_velocity_;
}

void
sge::audio_null::listener::linear_velocity(
	audio::vector const &p)
{
	linear_velocity_ = p;
}

sge::audio::angle const
sge::audio_null::listener::direction() const
{
	return direction_;
}

void
sge::audio_null::listener::direction(
	audio::angle const &d)
{
	direction_ = d;
}

