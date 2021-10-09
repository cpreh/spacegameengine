//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/core/blend/create.hpp>
#include <sge/opengl/state/core/blend/make_actors.hpp>
#include <sge/opengl/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::state::core::blend::object_unique_ptr sge::opengl::state::core::blend::create(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::blend::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::state::core::blend::object>(
      fcppt::make_unique_ptr<sge::opengl::state::core::blend::object>(
          sge::opengl::state::core::blend::make_actors(_context, _parameters)));
}
