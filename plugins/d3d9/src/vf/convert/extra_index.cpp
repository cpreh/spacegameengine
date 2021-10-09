//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/extra_index.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>

sge::renderer::vf::dynamic::index::value_type sge::d3d9::vf::convert::extra_index(
    sge::d3d9::vf::texture_coordinate_count const _texture_coordinates,
    sge::renderer::vf::dynamic::index const _index)
{
  return _texture_coordinates.get() + _index.get();
}
