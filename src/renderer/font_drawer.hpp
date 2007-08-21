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

#include <cstddef>
#include "../shared_ptr.hpp"
#include "font_types.hpp"

namespace sge
{

class font_drawer {
public:
	typedef std::size_t size_type;
	virtual void begin_rendering(size_type buffer_chars, font_dim size) = 0;
	virtual void draw_char(font_char, font_rect rect, const font_color* data) = 0;
	virtual void end_rendering() = 0;
	virtual ~font_drawer() {}
};

typedef shared_ptr<font_drawer> font_drawer_ptr;

}

#endif
