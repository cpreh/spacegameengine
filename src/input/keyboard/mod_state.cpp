/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/keyboard/mod_state.hpp>

sge::input::keyboard::mod_state::mod_state()
:
	shift_(false),
	alt_(false),
	ctrl_(false)
{}

bool
sge::input::keyboard::mod_state::shift() const
{
	return shift_;
}

bool
sge::input::keyboard::mod_state::alt() const
{
	return alt_;
}

bool
sge::input::keyboard::mod_state::ctrl() const
{
	return ctrl_;
}

void
sge::input::keyboard::mod_state::shift(
	bool const _shift
)
{
	shift_ = _shift;
}

void
sge::input::keyboard::mod_state::alt(
	bool const _alt
)
{
	alt_ = _alt;
}

void
sge::input::keyboard::mod_state::ctrl(
	bool const _ctrl
)
{
	ctrl_ = _ctrl;
}
