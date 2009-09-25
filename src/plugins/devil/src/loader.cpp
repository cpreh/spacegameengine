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
#include "../file.hpp"
#include "../error.hpp"
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>

sge::devil::loader::loader()
{
	ilEnable(IL_FORMAT_SET);
	ilSetInteger(IL_FORMAT_MODE, IL_RGBA);
	ilEnable(IL_FILE_OVERWRITE);
	check_errors();
}

sge::image::file_ptr const
sge::devil::loader::load(
	filesystem::path const &p)
{
	return make_shared_ptr<
		file
	>(
		p
	);
}

/*const sge::image::object_ptr
sge::devil::loader::load_image(
	const image::format::type type,
	const object::const_pointer format_data,
	const object::size_type size)
{
	return image::object_ptr(new object(type, format_data, size));
}*/

sge::image::file_ptr const
sge::devil::loader::create(
	image::view::const_object const &src)
{
	return make_shared_ptr<
		file
	>(
		src
	);
}

sge::extension_set const
sge::devil::loader::extensions() const
{
	// FIXME: add more extensions, see: http://openil.sourceforge.net/features.php
	extension_set s;
	s.insert(SGE_TEXT("bmp"));
	s.insert(SGE_TEXT("png"));
	s.insert(SGE_TEXT("jpg"));
	s.insert(SGE_TEXT("jpeg"));
	return s;
}
