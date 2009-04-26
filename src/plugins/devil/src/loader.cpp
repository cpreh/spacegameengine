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



#include "../loader.hpp"
#include "../object.hpp"
#include "../error.hpp"

sge::devil::loader::loader()
{
	ilEnable(IL_FORMAT_SET);
	ilSetInteger(IL_FORMAT_MODE, IL_RGBA);
	ilEnable(IL_FILE_OVERWRITE);
	check_errors();
}

sge::image::object_ptr const
sge::devil::loader::load(
	filesystem::path const &p)
{
	return image::object_ptr(
		new object(p));
}

/*const sge::image::object_ptr
sge::devil::loader::load_image(
	const image::format::type type,
	const object::const_pointer format_data,
	const object::size_type size)
{
	return image::object_ptr(new object(type, format_data, size));
}*/

sge::image::object_ptr const
sge::devil::loader::create(
	renderer::const_image_view const &src)
{
	return image::object_ptr(
		new object(src));
}
