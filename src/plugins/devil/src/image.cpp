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


#include "../image.hpp"
#include <IL/ilu.h>

sge::devil::image::image(const std::string& file)
{
	ILuint temp;
	ilGenImages(1,&temp);
	id = new im_guard(temp);
	bind_me();
	if(ilLoadImage(const_cast<char*>(file.c_str())) == IL_FALSE)
		throw std::runtime_error(std::string("ilLoadImage() failed! Could not load '") += file + "'!");
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
}

void sge::devil::image::bind_me() const
{
	ilBindImage(*id);
}

sge::image::size_type sge::devil::image::width() const
{
	return w;
}

sge::image::size_type sge::devil::image::height() const
{
	return h;
}

sge::image::const_pointer sge::devil::image::data() const
{
	bind_me();
	return reinterpret_cast<color*>(ilGetData());
}

void sge::devil::image::resize(const size_type _w, const size_type _h)
{
	if(_w == w && _h == h)
		return;
	bind_me();
	if(iluScale(_w,_h,32) == IL_FALSE)
		throw std::runtime_error("iluScale() failed!");
	w = _w;
	h = _h;
}
