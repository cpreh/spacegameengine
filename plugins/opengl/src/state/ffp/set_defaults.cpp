//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/set_defaults.hpp>
#include <sge/opengl/state/ffp/alpha_test/set.hpp>
#include <sge/opengl/state/ffp/clip_plane/set.hpp>
#include <sge/opengl/state/ffp/fog/set.hpp>
#include <sge/opengl/state/ffp/lighting/set.hpp>
#include <sge/opengl/state/ffp/lighting/light/set.hpp>
#include <sge/opengl/state/ffp/lighting/material/set.hpp>
#include <sge/opengl/state/ffp/misc/set.hpp>
#include <sge/opengl/state/ffp/sampler/set_defaults.hpp>
#include <sge/opengl/state/ffp/transform/set_defaults.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref.hpp>
#include <fcppt/log/object_fwd.hpp>

void sge::opengl::state::ffp::set_defaults(
    fcppt::log::object &_log, sge::opengl::context::object &_context)
{
  sge::opengl::state::ffp::alpha_test::set(
      _context, sge::renderer::state::ffp::alpha_test::const_optional_object_ref());

  sge::opengl::state::ffp::clip_plane::set(
      _context, sge::renderer::state::ffp::clip_plane::const_object_ref_vector());

  sge::opengl::state::ffp::fog::set(
      _context, sge::renderer::state::ffp::fog::const_optional_object_ref());

  sge::opengl::state::ffp::lighting::set(
      _context, sge::renderer::state::ffp::lighting::const_optional_object_ref());

  sge::opengl::state::ffp::lighting::light::set(
      _context, sge::renderer::state::ffp::lighting::light::const_object_ref_vector());

  sge::opengl::state::ffp::lighting::material::set(
      _context, sge::renderer::state::ffp::lighting::material::const_optional_object_ref());

  sge::opengl::state::ffp::misc::set(
      _log, _context, sge::renderer::state::ffp::misc::const_optional_object_ref());

  sge::opengl::state::ffp::sampler::set_defaults(_log, _context);

  sge::opengl::state::ffp::transform::set_defaults(_context);
}
