/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/display_mode.hpp>
#include <sge/text.hpp>
#include <ostream>
	
sge::renderer::display_mode::display_mode(
	screen_size_t const &size,
	bit_depth::type const depth,
	refresh_rate_type const refresh_rate)
 :
	size(size),
	depth(depth),
	refresh_rate(refresh_rate)
{}

sge::renderer::screen_unit
sge::renderer::display_mode::width() const
{
	return size.w();
}

sge::renderer::screen_unit
sge::renderer::display_mode::height() const
{
	return size.h();
}

bool sge::renderer::operator== (
	display_mode const &l,
	display_mode const &r)
{
	return l.depth == r.depth
		&& l.size == r.size
		&& l.refresh_rate == r.refresh_rate;
}

bool sge::renderer::operator!= (
	display_mode const &l,
	display_mode const &r)
{
	return !(l==r);
}

sge::ostream &
sge::renderer::operator<<(
	ostream &s,
	display_mode const &mode)
{
	return s << SGE_TEXT('(')
	         << mode.width()
	         << SGE_TEXT('x')
	         << mode.height()
	         << SGE_TEXT('x')
	         << mode.depth
	         << SGE_TEXT('@')
	         << mode.refresh_rate
	         << SGE_TEXT(')');
}
