/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_COLOR_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_COLOR_FORMAT_TYPES_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/opengl/texture/color_format_types_fwd.hpp>
#include <sge/opengl/texture/convert_format_function.hpp>
#include <sge/opengl/texture/convert_format_type_function.hpp>
#include <sge/opengl/texture/convert_internal_format_function.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct color_format_types
{
	typedef sge::image::color::format format;

	static
	format
	best_format(
		sge::renderer::texture::color_format const &
	);

	typedef sge::opengl::texture::convert_format_function<
		format
	>::type convert_format_function_type;

	static
	convert_format_function_type
	convert_format();

	typedef sge::opengl::texture::convert_format_type_function<
		format
	>::type convert_format_type_function;

	static
	convert_format_type_function
	convert_format_type();

	typedef sge::opengl::texture::convert_internal_format_function<
		format
	>::type convert_internal_format_function;

	static
	convert_internal_format_function
	convert_internal_format();

	static
	format
	translate_format(
		format,
		sge::renderer::texture::color_format const &
	);
};

}
}
}

#endif
