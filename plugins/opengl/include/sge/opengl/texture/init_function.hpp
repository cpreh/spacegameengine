//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_INIT_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_INIT_FUNCTION_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/renderer/basic_dim_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/size_type.hpp>

namespace sge::opengl::texture
{

template <fcppt::math::size_type Size>
using init_function = fcppt::reference<void(
    sge::opengl::texture::binding const &,
    sge::opengl::texture::config<Size> const &,
    sge::opengl::texture::buffer_type,
    sge::opengl::color_order,
    sge::opengl::color_base_type,
    sge::opengl::internal_color_format,
    sge::renderer::texture::mipmap::level,
    sge::renderer::basic_dim<Size> const &,
    sge::renderer::const_raw_pointer)>;

}

#endif
