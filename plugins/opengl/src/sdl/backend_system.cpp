//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/sdl/backend_system.hpp>
#include <sge/opengl/sdl/context.hpp>
#include <sge/opengl/sdl/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/system/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::sdl::backend_system::backend_system(awl::backends::sdl::system::object_ref)
    : sge::opengl::backend::system{}, init_video_{SDL_INIT_VIDEO}
{
}

sge::opengl::sdl::backend_system::~backend_system() = default;

awl::visual::object_unique_ptr sge::opengl::sdl::backend_system::create_visual(
    sge::renderer::pixel_format::object const &_pixel_format)
{
  return fcppt::unique_ptr_to_base<awl::visual::object>(
      fcppt::make_unique_ptr<sge::opengl::sdl::visual>(_pixel_format));
}

sge::opengl::backend::context_unique_ptr
sge::opengl::sdl::backend_system::create_context(sge::window::object_ref const _window)
{
  return fcppt::unique_ptr_to_base<sge::opengl::backend::context>(
      fcppt::make_unique_ptr<sge::opengl::sdl::context>(_window));
}
