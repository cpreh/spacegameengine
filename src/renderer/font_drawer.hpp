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


#ifndef SGE_FONT_DRAWER_HPP_INCLUDED
#define SGE_FONT_DRAWER_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../font/char_metric.hpp"
#include "font_types.hpp"

namespace sge
{

class font_drawer {
public:
	virtual void draw_char(char_metric_ptr metric, font_pos pos, font_unit font_height, color col) = 0;
	virtual void flush() = 0;
	virtual ~font_drawer() {}
};

typedef shared_ptr<font_drawer> font_drawer_ptr;

}

#endif
