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
