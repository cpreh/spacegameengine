//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/set_or_default.hpp>
#include <sge/d3d9/state/core/rasterizer/object.hpp>
#include <sge/d3d9/state/core/rasterizer/set.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>

void sge::d3d9::state::core::rasterizer::set(
    sge::renderer::state::core::rasterizer::const_optional_object_ref const &_state,
    sge::d3d9::state::core::rasterizer::object const &_default)
{
  sge::d3d9::state::set_or_default(_state, _default);
}
