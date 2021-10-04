//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_FORMAT_TYPES_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/opengl/texture/convert_base_type_function.hpp>
#include <sge/opengl/texture/convert_internal_format_function.hpp>
#include <sge/opengl/texture/convert_order_function.hpp>
#include <sge/opengl/texture/depth_stencil_format_types_fwd.hpp>
#include <sge/opengl/texture/format_result_fwd.hpp>


namespace sge::opengl::texture
{

struct depth_stencil_format_types
{
	using
	format
	=
	sge::image::ds::format;

	using
	gl_format
	=
	format;

	using
	convert_order_function_type
	=
	sge::opengl::texture::convert_order_function<
		format
	>;

	[[nodiscard]]
	static
	convert_order_function_type
	convert_order();

	using
	convert_base_type_function
	=
	sge::opengl::texture::convert_base_type_function<
		format
	>;

	[[nodiscard]]
	static
	convert_base_type_function
	convert_base_type();

	using
	convert_internal_format_function
	=
	sge::opengl::texture::convert_internal_format_function<
		format
	>;

	[[nodiscard]]
	static
	convert_internal_format_function
	convert_internal_format();

	using
	format_result
	=
	sge::opengl::texture::format_result<
		format,
		gl_format
	>;

	[[nodiscard]]
	static
	format_result
	translate_format(
		format
	);
};

}

#endif
