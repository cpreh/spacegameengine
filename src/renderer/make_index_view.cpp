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


#include <sge/renderer/make_index_view.hpp>
#include <sge/renderer/index_format_stride.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::renderer::dynamic_index_view const
sge::renderer::make_index_view(
	unsigned char * const data,
	std::size_t const sz,
	index_format::type const format)
{
	switch(index_format_stride(format)) {
	case sizeof(uint16):
		return renderer::index_view_16(
			reinterpret_cast<renderer::index_view_16::pointer>(
				data),
			sz);
	case sizeof(uint32):
		return renderer::index_view_32(
			reinterpret_cast<renderer::index_view_32::pointer>(
				data),
			sz);
	default:
		throw exception(SGE_TEXT("Invalid stride in ogl::index_buffer::view()!"));
	}
}
	
sge::renderer::const_dynamic_index_view const
sge::renderer::make_index_view(
	unsigned char const * const data,
	std::size_t const sz,
	index_format::type const format)
{
	switch(index_format_stride(format)) {
	case sizeof(uint16):
		return renderer::const_index_view_16(
			reinterpret_cast<renderer::const_index_view_16::pointer>(
				data),
			sz);
	case sizeof(uint32):
		return renderer::const_index_view_32(
			reinterpret_cast<renderer::const_index_view_32::pointer>(
				data),
			sz);
	default:
		throw exception(SGE_TEXT("Invalid stride in ogl::index_buffer::view()!"));
	}
}
