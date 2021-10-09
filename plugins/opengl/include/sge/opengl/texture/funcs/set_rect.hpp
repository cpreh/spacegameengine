//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_SET_RECT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_SET_RECT_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/surface_config_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>

namespace sge::opengl::texture::funcs
{

void set_rect(
    sge::opengl::texture::binding const &,
    sge::opengl::context::object &, // NOLINT(google-runtime-references)
    sge::opengl::texture::surface_config const &,
    sge::opengl::texture::buffer_type,
    sge::opengl::color_order,
    sge::opengl::color_base_type,
    sge::renderer::texture::mipmap::level,
    sge::renderer::dim2 const &,
    sge::renderer::lock_rect const &,
    sge::renderer::const_raw_pointer src);

}

#endif
