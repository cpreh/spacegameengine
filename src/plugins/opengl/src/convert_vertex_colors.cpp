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


#include "../convert_vertex_colors.hpp"
#include <sge/renderer/vf/dynamic_color.hpp>
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <sge/renderer/convert_pixels_conditional.hpp>
#include <boost/variant/get.hpp>
#include <boost/assign/list_of.hpp>

void sge::ogl::convert_vertex_colors(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::size_type const vertex_stride,
	renderer::size_type const num_vertices,
	unsigned char *const data)
{
	sge::renderer::vf::dynamic_color const dcolor(
		boost::get<sge::renderer::vf::dynamic_color>(
			e.element().info()));

	sge::renderer::convert_pixels_conditional(
		data + e.offset(),
		sge::renderer::dim_type(
			1,
			num_vertices),
		dcolor.color_format(),
		vertex_stride,
		boost::assign::list_of
			(sge::renderer::color_format::rgba8)
			(sge::renderer::color_format::rgba32f));
}
