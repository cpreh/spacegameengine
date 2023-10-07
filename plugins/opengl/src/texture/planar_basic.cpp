//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/traits/dimension.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/view/const_object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/view/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/basic_box_impl.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/buffer_surface_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/color_format_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/color_surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/planar_basic.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/planar_types.hpp>
#include <sge/renderer/color_buffer/surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/planar_parameters.hpp> // NOLINT(misc-include-cleaner)

template class sge::opengl::texture::basic<sge::opengl::texture::planar_types>;

template class sge::opengl::texture::basic_box<sge::opengl::texture::planar_types>;
