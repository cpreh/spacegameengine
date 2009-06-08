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


#include <sge/renderer/index/format_stride.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::renderer::size_type
sge::renderer::index::format_stride(
	format::type const f)
{
	switch(f) {
	case format::i16:
		return sizeof(view_16::value_type);
	case format::i32:
		return sizeof(view_32::value_type);
	default:
		throw exception(
			SGE_TEXT("Invalid index::format in index::format_stride()!"));
	}
}
