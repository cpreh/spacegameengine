//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/ffp/clip_plane/state.hpp>
#include <sge/renderer/state/ffp/clip_plane/area.hpp>

sge::d3d9::state::ffp::clip_plane::state::state(
    sge::renderer::state::ffp::clip_plane::area const &_area)
    : area_(_area)
{
}

sge::renderer::state::ffp::clip_plane::area const &
sge::d3d9::state::ffp::clip_plane::state::area() const
{
  return area_;
}
