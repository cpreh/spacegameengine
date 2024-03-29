//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/current.hpp>
#include <sge/opengl/egl/surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::context::context(
    EGLDisplay const _display, // NOLINT(misc-misplaced-const)
    EGLConfig const _config, // NOLINT(misc-misplaced-const)
    sge::opengl::egl::surface_unique_ptr &&_surface)
    : sge::opengl::backend::context(),
      display_{_display},
      surface_{std::move(_surface)},
      context_{_display, _config}
{
}

sge::opengl::egl::context::~context() = default;

sge::opengl::backend::current_unique_ptr sge::opengl::egl::context::activate()
{
  this->context_.activate(this->surface_->get());

  return fcppt::unique_ptr_to_base<sge::opengl::backend::current>(
      fcppt::make_unique_ptr<sge::opengl::egl::current>(
          sge::opengl::egl::current::display_type{this->display_},
          sge::opengl::egl::current::surface_type{this->surface_->get()}));
}

// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
void sge::opengl::egl::context::deactivate(sge::opengl::backend::current_unique_ptr &&)
{
  this->context_.deactivate();
}
