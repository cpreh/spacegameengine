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


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_FORMAT_TYPES_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/opengl/texture/convert_base_type_function.hpp>
#include <sge/opengl/texture/convert_internal_format_function.hpp>
#include <sge/opengl/texture/convert_order_function.hpp>
#include <sge/opengl/texture/depth_stencil_format_types_fwd.hpp>
#include <sge/opengl/texture/format_result_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct depth_stencil_format_types
{
	typedef
	sge::image::ds::format
	format;

	typedef
	format
	gl_format;

	typedef
	sge::opengl::texture::convert_order_function<
		format
	>
	convert_order_function_type;

	static
	convert_order_function_type
	convert_order();

	typedef
	sge::opengl::texture::convert_base_type_function<
		format
	>
	convert_base_type_function;

	static
	convert_base_type_function
	convert_base_type();

	typedef
	sge::opengl::texture::convert_internal_format_function<
		format
	>
	convert_internal_format_function;

	static
	convert_internal_format_function
	convert_internal_format();

	typedef
	sge::opengl::texture::format_result<
		format,
		gl_format
	>
	format_result;

	static
	format_result
	translate_format(
		format
	);
};

}
}
}

#endif
