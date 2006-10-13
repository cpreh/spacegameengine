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


#include "../image_loader.hpp"
#include "../image.hpp"

sge::devil::image_loader::image_loader()
{
	ilEnable(IL_FORMAT_SET);
	ilSetInteger(IL_FORMAT_MODE,IL_RGBA);
}

sge::image_ptr sge::devil::image_loader::load_image(const std::string& path, const unsigned w, const unsigned h)
{
	image_ptr im(new image(path));
	
	if(w && h)
		im->resize(w,h);

	return im;
}

