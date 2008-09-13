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


#include <sge/renderer/image_view_format.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::renderer::color_format::type
sge::renderer::image_view_format(
	const_image_view const &view)
{
	if(view.current_type_is<rgba8_view>())
		return color_format::rgba8;
	if(view.current_type_is<argb8_view>())
		return color_format::argb8;
	if(view.current_type_is<bgra8_view>())
		return color_format::bgra8;
	throw exception(
		SGE_TEXT("Unknown view type in image_view_format()!"));
}
