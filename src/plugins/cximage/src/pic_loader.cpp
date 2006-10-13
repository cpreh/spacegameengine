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


#include "../pic_loader.hpp"
#include "../../core/renderer/lock_ptr.hpp"
#include <CxImage/ximage.h>

namespace {
	inline void error(const std::string& file)
	{
		throw std::runtime_error(std::string("Cannot load image: ") + file);
	}
	inline void do_work(CxImage& img, const std::string& file, unsigned w, unsigned h)
	{
		img = CxImage(file.c_str(),CXIMAGE_FORMAT_UNKNOWN);
		if(!img.IsValid())
			Error(Path);
		if(!img.AlphaIsValid())
			Img.AlphaCreate();
		if(w != 0 || h != 0)
			img.Resample2(w,h,CxImage::IM_BICUBIC2,CxImage::OM_TRANSPARENT);
	}
}

void sge::cximage::pic_loader::create_pic(const std::string& file, pixel_array& array,
                                          unsigned w, unsigned h)
{
	CxImage img;
	DoWork(img,file,w,h);
	array.clear();
	array.reserve(img.GetWidth(),img.GetHeight());
	for(unsigned y = img.GetHeight()-1; y > 0; --y)
		for(unsigned x = 0; x < img.GetWidth(); ++x)
		{
			const RGBQUAD q = img.GetPixelColor(x,y);
			array.push_back((q.rgbReserved << 24) | (q.rgbRed << 16) | (q.rgbGreen << 8) | q.rgbBlue);
		}
}

sge::texture_ptr sge::cximage::pic_loader::create_texture(renderer_ptr device,  const std::string& file,
                                                          unsigned mip_levels, unsigned flags,
                                                          unsigned w, unsigned h)
{
	CxImage img;
	DoWork(img,file,w,h);
	texture_ptr tex = device->create_texture(img.GetWidth(),img.GetHeight(),mip_levels,flags);
	lock_ptr<texture> l(tex,LF_Discard);
	texture::iterator dest = tex->begin();
	for(unsigned y = img.GetHeight()-1; y > 0; --y)
		for(unsigned x = 0; x < img.GetWidth(); ++x)
		{
			const RGBQUAD q = img.GetPixelColor(x,y);
			(*dest++) = (q.rgbReserved << 24) | (q.rgbRed << 16) | (q.rgbGreen << 8) | q.rgbBlue;
		}
	return tex;
}
