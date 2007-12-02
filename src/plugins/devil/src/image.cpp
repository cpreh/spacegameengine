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


#include "../../../exception.hpp"
#include "../image.hpp"
#include "../error.hpp"
#include "../conversion.hpp"
#include <IL/ilu.h>

sge::devil::image::image(const std::string& file)
{
	bind_me();
	if(ilLoadImage(const_cast<char*>(file.c_str())) == IL_FALSE)
		throw exception(std::string("ilLoadImage() failed! Could not load '") += file + "'!");
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
	check_errors();
}

sge::devil::image::image(const image_format::type type, const const_pointer format_data, const size_type size)
{
	if(!format_data || size == 0)
		throw exception("load_image(): format_data or size is 0!");
	bind_me();
	if(ilLoadL(convert_cast<ILenum>(type), const_cast<pointer>(format_data), static_cast<ILuint>(size)) == IL_FALSE)
		throw exception("ilLoadL() failed!");
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);

}

sge::devil::image::image(const const_pointer p, const size_type w, const size_type h)
 : w(w), h(h)
{
	bind_me();
	if(p)
		data(p);
}

void sge::devil::image::bind_me() const
{
	ilBindImage(impl.id());
	check_errors();
}

sge::image::size_type sge::devil::image::width() const
{
	return w;
}

sge::image::size_type sge::devil::image::height() const
{
	return h;
}

void sge::devil::image::data(const const_pointer p)
{
	bind_me();
	ilTexImage(static_cast<ILuint>(width()),
	           static_cast<ILuint>(height()),
	           1,
	           4,
	           IL_RGBA,IL_UNSIGNED_BYTE,
	           const_cast<pointer>(p));
	check_errors();
}

sge::image::const_pointer sge::devil::image::data() const
{
	bind_me();
	return reinterpret_cast<const_pointer>(ilGetData());
}

void sge::devil::image::resample(const size_type _w, const size_type _h)
{
	if(width() == _w && height() == _h)
		return;
	bind_me();
	iluScale(static_cast<ILuint>(_w), static_cast<ILuint>(_h), 32);
	check_errors();
	w = _w;
	h = _h;
}

void sge::devil::image::save(const std::string& path)
{
	bind_me();
	ilSaveImage(const_cast<char*>(path.c_str()));
}
