//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image3d/traits/dimension.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/opengl/texture/basic_box_impl.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/buffer_volume_types.hpp>
#include <sge/opengl/texture/color_format_types.hpp>
#include <sge/opengl/texture/color_volume.hpp>
#include <sge/opengl/texture/volume_basic.hpp>
#include <sge/opengl/texture/volume_types.hpp>
#include <sge/renderer/color_buffer/volume.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>

template class sge::opengl::texture::basic<sge::opengl::texture::volume_types>;

template class sge::opengl::texture::basic_box<sge::opengl::texture::volume_types>;
