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


#include "../image_loader.hpp"
#include "../image.hpp"
#include "../error.hpp"

sge::devil::image_loader::image_loader()
{
	ilEnable(IL_FORMAT_SET);
	ilSetInteger(IL_FORMAT_MODE,IL_RGBA);
	ilEnable(IL_FILE_OVERWRITE);
	check_errors();
}

sge::image_ptr sge::devil::image_loader::load_image(const path& p)
{
	return image_ptr(new image(p));
}

sge::image_ptr sge::devil::image_loader::load_image(const image_format::type type, const image::const_pointer format_data, const image::size_type size)
{
	return image_ptr(new image(type, format_data, size));
}

sge::image_ptr sge::devil::image_loader::create_image(const image::const_pointer p, const image::dim_type& dim)
{
	return image_ptr(new image(p, dim));
}
