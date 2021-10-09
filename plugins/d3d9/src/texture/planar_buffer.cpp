//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/texture/basic_buffer_impl.hpp>
#include <sge/d3d9/texture/planar_buffer.hpp>
#include <sge/d3d9/texture/planar_types.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp>

template class sge::d3d9::texture::basic_buffer<sge::d3d9::texture::planar_types>;
