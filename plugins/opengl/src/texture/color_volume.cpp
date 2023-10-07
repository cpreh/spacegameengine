//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/traits/format_stride.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/algorithm/copy.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/const_object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/flipped.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/make.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/sub.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/to_const.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/basic_buffer_impl.hpp>
#include <sge/opengl/texture/basic_lockable_buffer_impl.hpp>
#include <sge/opengl/texture/buffer_volume_types.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/color_volume.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/color_volume_types.hpp>

template class sge::opengl::texture::basic_buffer<sge::opengl::texture::color_volume_types>;

template class sge::opengl::texture::basic_lockable_buffer<
    sge::opengl::texture::color_volume_types>;
