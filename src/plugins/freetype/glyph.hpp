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



#ifndef SGE_FT_GLYPH_HPP_INCLUDED
#define SGE_FT_GYLPH_HPP_INCLUDED

#include "freetype.hpp"
#include FT_GLYPH_H
#include <sge/noncopyable.hpp>

namespace sge
{
namespace ft
{

class face;

class glyph {
	SGE_NONCOPYABLE(glyph)
public:
	explicit glyph(
		face const &);
	~glyph();
	FT_BitmapGlyph bitmap_glyph() const;
private:
	FT_Glyph glyph_;
};

}
}

#endif
