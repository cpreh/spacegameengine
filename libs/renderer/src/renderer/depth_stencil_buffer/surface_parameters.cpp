//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>

sge::renderer::depth_stencil_buffer::surface_parameters::surface_parameters(
    sge::renderer::dim2 const _size, sge::image::ds::format const _format)
    : size_(_size), format_(_format)
{
}

sge::renderer::dim2 const &sge::renderer::depth_stencil_buffer::surface_parameters::size() const
{
  return size_;
}

sge::image::ds::format sge::renderer::depth_stencil_buffer::surface_parameters::format() const
{
  return format_;
}
