//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/current_ref.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/target/create_onscreen.hpp>
#include <sge/opengl/target/onscreen.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/onscreen_unique_ptr.hpp>
#include <awl/window/object_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::target::onscreen_unique_ptr sge::opengl::target::create_onscreen(
    sge::opengl::context::object_ref const _context,
    sge::opengl::backend::current_ref const _current,
    awl::window::object_ref const _window)
{
  return fcppt::unique_ptr_to_base<sge::renderer::target::onscreen>(
      fcppt::make_unique_ptr<sge::opengl::target::onscreen>(_context, _current, _window));
}
