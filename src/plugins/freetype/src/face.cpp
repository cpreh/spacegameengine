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


#include "../../../iconv.hpp"
#include "../../../exception.hpp"
#include "../library.hpp"
#include "../face.hpp"

sge::ft::face::face(library& lib, const path& name)
{
	if(FT_New_Face(lib.lib(), iconv(name.string()).c_str(), 0, &impl))
		throw exception(string(SGE_TEXT("FT_New_Face() failed for font: ")) += name.string());
}

sge::ft::face::~face()
{
	FT_Done_Face(impl);
}

FT_Face sge::ft::face::get() const
{
	return impl;
}

FT_Face sge::ft::face::operator->() const
{
	return get();
}
