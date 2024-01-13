//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/image/ds/traits/format_fwd.hpp> // IWYU pragma: keep
#include <sge/imageds2d/traits/color_tag.hpp> // IWYU pragma: keep
#include <sge/imageds2d/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/depth_stencil_surface_fwd.hpp> // IWYU pragma: keep
#include <sge/opengl/texture/depth_stencil_surface_types.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern template class sge::opengl::texture::basic_buffer<
    sge::opengl::texture::depth_stencil_surface_types>;

FCPPT_PP_POP_WARNING

#endif
