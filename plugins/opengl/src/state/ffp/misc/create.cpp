//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/ffp/misc/create.hpp>
#include <sge/opengl/state/ffp/misc/make_actors.hpp>
#include <sge/opengl/state/ffp/misc/object.hpp>
#include <sge/renderer/state/ffp/misc/object.hpp>
#include <sge/renderer/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>

sge::renderer::state::ffp::misc::object_unique_ptr sge::opengl::state::ffp::misc::create(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::ffp::misc::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::state::ffp::misc::object>(
      fcppt::make_unique_ptr<sge::opengl::state::ffp::misc::object>(
          sge::opengl::state::ffp::misc::make_actors(_log, _context, _parameters)));
}
