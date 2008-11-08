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


#ifndef SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED

#include "bit_depth.hpp"
#include "screen_types.hpp"
#include "../export.hpp"
#include "../ostream.hpp"

namespace sge
{
namespace renderer
{

typedef unsigned refresh_rate_type;

struct display_mode {
	SGE_SYMBOL display_mode(
		screen_size_t const &sz,
		bit_depth::type depth,
		refresh_rate_type refresh_rate = 0);
	
	screen_size_t     size;
	bit_depth::type   depth;
	refresh_rate_type refresh_rate;

	SGE_SYMBOL screen_unit width() const;
	SGE_SYMBOL screen_unit height() const;
};

SGE_SYMBOL ostream &
operator<<(
	ostream &,
	display_mode const &mode);

SGE_SYMBOL bool operator== (
	display_mode const &l,
	display_mode const &r);

SGE_SYMBOL bool operator!= (
	display_mode const &l,
	display_mode const &r);

}
}

#endif
