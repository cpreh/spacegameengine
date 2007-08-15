/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../types.hpp"
#include "../../exception.hpp"

unsigned sge::bit_depth_bit_count(const bit_depth::type d)
{
	switch(d) {
	case bit_depth::depth16:
		return 16;
	case bit_depth::depth32:
		return 32;
	}
	throw exception("Invalid bit_depth!");
}

sge::display_mode::display_mode(const screen_unit width, const screen_unit height, const bit_depth::type depth, const unsigned refresh_rate)
 : size(width,height), depth(depth), refresh_rate(refresh_rate)
{}

sge::screen_unit sge::display_mode::width() const
{
	return size.w();
}

sge::screen_unit sge::display_mode::height() const
{
	return size.h();
}

std::ostream& sge::operator<< (std::ostream& s, const display_mode& mode)
{
	return s << '(' << mode.width() << 'x' << mode.height() << 'x' << bit_depth_bit_count(mode.depth) << '@' << mode.refresh_rate << ')';
}

std::wostream& sge::operator<< (std::wostream& s, const display_mode& mode)
{
	return s << L'(' << mode.width() << L'x' << mode.height() << L'x' << bit_depth_bit_count(mode.depth) << L'@' << mode.refresh_rate << L')';
}
