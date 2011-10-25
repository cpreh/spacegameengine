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


#include <sge/cegui/default_font.hpp>
#include <fcppt/filesystem/path.hpp>


sge::cegui::default_font::default_font(
	fcppt::filesystem::path const &_path,
	float const _font_size
)
:
	path_(_path),
	font_size_(_font_size)
{
}

fcppt::filesystem::path const &
sge::cegui::default_font::path() const
{
	return path_;
}

float
sge::cegui::default_font::font_size() const
{
	return font_size_;
}
