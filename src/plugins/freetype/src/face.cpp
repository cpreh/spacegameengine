/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/freetype/library.hpp>
#include <sge/freetype/face.hpp>
#include <sge/freetype/freetype.hpp>
#include <sge/font/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/filesystem/path_to_string.hpp>


sge::freetype::face::face(
	library &_lib,
	fcppt::filesystem::path const &_name
)
{
	if(
		FT_New_Face(
			_lib.lib(),
			fcppt::to_std_string(
				fcppt::filesystem::path_to_string(
					_name
				)
			).c_str(),
			0,
			&impl_
		)
	)
		throw font::exception(
			FCPPT_TEXT("FT_New_Face() failed for font: ")
			+
			fcppt::filesystem::path_to_string(
				_name
			)
		);
}

sge::freetype::face::~face()
{
	FT_Done_Face(
		impl_
	);
}

FT_Face
sge::freetype::face::get() const
{
	return impl_;
}

FT_Face
sge::freetype::face::operator->() const
{
	return this->get();
}
