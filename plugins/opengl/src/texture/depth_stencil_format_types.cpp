//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/depth_stencil_base_type.hpp>
#include <sge/opengl/convert/depth_stencil_order.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <sge/opengl/texture/depth_stencil_format_types.hpp>
#include <sge/opengl/texture/format_result_impl.hpp>

sge::opengl::texture::depth_stencil_format_types::convert_order_function_type
sge::opengl::texture::depth_stencil_format_types::convert_order()
{
  return sge::opengl::convert::depth_stencil_order;
}

sge::opengl::texture::depth_stencil_format_types::convert_base_type_function
sge::opengl::texture::depth_stencil_format_types::convert_base_type()
{
  return sge::opengl::convert::depth_stencil_base_type;
}

sge::opengl::texture::depth_stencil_format_types::convert_internal_format_function
sge::opengl::texture::depth_stencil_format_types::convert_internal_format()
{
  return sge::opengl::convert::depth_stencil_to_internal_format;
}

sge::opengl::texture::depth_stencil_format_types::format_result
sge::opengl::texture::depth_stencil_format_types::translate_format(
    sge::opengl::texture::depth_stencil_format_types::format const _format)
{
  return sge::opengl::texture::depth_stencil_format_types::format_result{_format, _format};
}
