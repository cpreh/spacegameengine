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

sge::cximage::image::image(const std::string& file, const unsigned w, const unsigned h)
 : img(file.c_str(),CXIMAGE_FORMAT_UNKNOWN)
{
	if(!img.IsValid())
		throw std::runtime_error(std::string("Loading ") += file + " with cximage failed!")
	if(!img.AlphaIsValid())
		Img.AlphaCreate();
	if(w != 0 || h != 0)
		resize(w,h);
}

void sge::cximage::image::resize(const size_type w, const size_type h)
{
	img.Resample2(w, h, CxImage::IM_BICUBIC2, CxImage::OM_TRANSPARENT);
}

sge::image::const_pointer sge::cximage::image::data() const
{
	return 0; // FIXME
}

sge::image::size_type sge::cximage::image::width() const
{
	return img.GetWidth();
}

sge::image::size_type sge::cximage::image::height() const
{
	return img.GetHeight();
}
