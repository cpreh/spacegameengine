//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/object_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::core::rasterizer::scoped::scoped(
    sge::renderer::context::core_ref const _context,
    fcppt::reference<sge::renderer::state::core::rasterizer::object const> const _object)
    : context_(_context)
{
  context_.get().rasterizer_state(
      sge::renderer::state::core::rasterizer::const_optional_object_ref(_object));
}

sge::renderer::state::core::rasterizer::scoped::~scoped()
{
  context_.get().rasterizer_state(
      sge::renderer::state::core::rasterizer::const_optional_object_ref());
}
