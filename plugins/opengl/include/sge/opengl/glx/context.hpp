//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_GLX_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLX_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/glx/context_fwd.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <awl/backends/x11/window/base_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::glx
{

class context : public sge::opengl::backend::context
{
  FCPPT_NONMOVABLE(context);

public:
  context(
      fcppt::log::object_reference,
      awl::backends::x11::window::base_ref,
      sge::opengl::glx::optional_proc_address_function);

  ~context() override;

private:
  [[nodiscard]] sge::opengl::backend::current_unique_ptr activate() override;

  void deactivate(sge::opengl::backend::current_unique_ptr &&) override;

  fcppt::log::object_reference const log_;

  awl::backends::x11::window::base_ref const window_;

  sge::opengl::glx::optional_proc_address_function const proc_address_;

  GLXContext const context_; // NOLINT(misc-misplaced-const)
};

}

#endif
