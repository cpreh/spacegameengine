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


#include "element_converter.hpp"

sge::renderer::vf:;dynamic::detail::element_converter::element_converter(
	sge::image::color::format::type const _original_color,
	sge::image::color::format::type const _backend_color,
	sge::renderer::vf::vertex_size const _stride,
	sge::renderer::vf::vertex_size const _offset
)
:
	original_color_(_original_color),
	backend_color_(_backend_color),
	stride_(_stride),
	offset_(_offset)
{
}

sge::renderer::vf:;dynamic::detail::element_converter::~element_converter();

void
sge::renderer::vf:;dynamic::detail::element_converter::convert(
	interval,
	sge::renderer::pointer data,
	bool unlock
);

