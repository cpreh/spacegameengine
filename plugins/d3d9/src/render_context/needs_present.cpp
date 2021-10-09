//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/render_context/needs_present.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/renderer/context/core_fwd.hpp>

bool sge::d3d9::render_context::needs_present(sge::renderer::context::core const &_context)
{
  return static_cast<sge::d3d9::render_context::object const &>(_context).needs_present();
}
