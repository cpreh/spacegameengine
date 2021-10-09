//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/check_state_once.hpp>
#include <sge/opengl/render_context/end.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/renderer/context/core.hpp>
#include <fcppt/cast/static_downcast.hpp>

void sge::opengl::render_context::end(sge::renderer::context::core &_context)
{
  sge::opengl::check_state_once();

  fcppt::cast::static_downcast<sge::opengl::render_context::object &>(_context).end_rendering();
}
