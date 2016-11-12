/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/convert/depth_stencil_base_type.hpp>
#include <sge/opengl/convert/depth_stencil_order.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <sge/opengl/texture/depth_stencil_format_types.hpp>
#include <sge/opengl/texture/format_result_impl.hpp>


sge::opengl::texture::depth_stencil_format_types::convert_order_function_type
sge::opengl::texture::depth_stencil_format_types::convert_order()
{
	return
		sge::opengl::convert::depth_stencil_order;
}

sge::opengl::texture::depth_stencil_format_types::convert_base_type_function
sge::opengl::texture::depth_stencil_format_types::convert_base_type()
{
	return
		sge::opengl::convert::depth_stencil_base_type;
}

sge::opengl::texture::depth_stencil_format_types::convert_internal_format_function
sge::opengl::texture::depth_stencil_format_types::convert_internal_format()
{
	return
		sge::opengl::convert::depth_stencil_to_internal_format;
}

sge::opengl::texture::depth_stencil_format_types::format_result
sge::opengl::texture::depth_stencil_format_types::translate_format(
	sge::opengl::texture::depth_stencil_format_types::format const _format
)
{
	return
		sge::opengl::texture::depth_stencil_format_types::format_result{
			_format,
			_format
		};
}
