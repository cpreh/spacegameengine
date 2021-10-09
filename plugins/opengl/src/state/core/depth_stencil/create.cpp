//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/core/depth_stencil/create.hpp>
#include <sge/opengl/state/core/depth_stencil/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::state::core::depth_stencil::object_unique_ptr
sge::opengl::state::core::depth_stencil::create(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::depth_stencil::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::state::core::depth_stencil::object>(
      fcppt::make_unique_ptr<sge::opengl::state::core::depth_stencil::object>(
          sge::opengl::state::core::depth_stencil::make_actors(_context, _parameters)));
}
