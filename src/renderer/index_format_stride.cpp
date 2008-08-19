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


#include <sge/renderer/index_format_stride.hpp>
#include <sge/renderer/index_view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

std::size_t sge::renderer::index_format_stride(
	index_format::type const f)
{
	switch(f) {
	case index_format::index16:
		return sizeof(index_view_16::value_type);
	case index_format::index32:
		return sizeof(index_view_32::value_type);
	default:
		throw exception(
			SGE_TEXT("Invalid index_format in index_format_stride()!"));
	}
}
