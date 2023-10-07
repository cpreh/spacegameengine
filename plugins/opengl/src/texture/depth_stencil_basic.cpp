//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/imageds2d/traits/dimension.hpp> // NOLINT(misc-include-cleaner)
#include <sge/imageds2d/view/const_object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/imageds2d/view/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/basic_box_impl.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/buffer_surface_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/depth_stencil_basic.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/depth_stencil_format_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/depth_stencil_surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/depth_stencil_types.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/depth_stencil.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/depth_stencil_parameters.hpp> // NOLINT(misc-include-cleaner)

template class sge::opengl::texture::basic<sge::opengl::texture::depth_stencil_types>;

template class sge::opengl::texture::basic_box<sge::opengl::texture::depth_stencil_types>;
