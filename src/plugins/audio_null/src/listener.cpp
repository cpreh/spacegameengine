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


#include "../listener.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sge::audio_null::listener::listener()
:
	pos_(
		audio::vector::null()
	),
	vel_(
		audio::vector::null()
	),
	direction_()
{}

sge::audio::vector const
sge::audio_null::listener::pos() const
{
	return pos_;
}

void
sge::audio_null::listener::pos(
	audio::vector const &p)
{
	pos_ = p;
}

sge::audio::vector const
sge::audio_null::listener::vel() const
{
	return vel_;
}

void
sge::audio_null::listener::vel(
	audio::vector const &p)
{
	vel_ = p;
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

