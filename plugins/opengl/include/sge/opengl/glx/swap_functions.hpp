//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_GLX_SWAP_FUNCTIONS_HPP_INCLUDED
#define SGE_OPENGL_GLX_SWAP_FUNCTIONS_HPP_INCLUDED

#include <sge/opengl/glx/proc_address_function.hpp>
#include <sge/opengl/glx/swap_functions_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::glx
{

class swap_functions
{
public:
  explicit swap_functions(sge::opengl::glx::proc_address_function);

  using glx_swap_interval_sgi = int(int);

  using optional_glx_swap_interval_sgi = fcppt::optional::reference<glx_swap_interval_sgi>;

  using glx_swap_interval_sgi_ref = optional_glx_swap_interval_sgi::value_type;

  using glx_swap_interval_ext = void(Display *, GLXDrawable, int);

  using optional_glx_swap_interval_ext = fcppt::optional::reference<glx_swap_interval_ext>;

  using glx_swap_interval_ext_ref = optional_glx_swap_interval_ext::value_type;

  [[nodiscard]] optional_glx_swap_interval_sgi swap_interval_sgi() const;

  [[nodiscard]] optional_glx_swap_interval_ext swap_interval_ext() const;

private:
  optional_glx_swap_interval_sgi swap_interval_sgi_;

  optional_glx_swap_interval_ext swap_interval_ext_;
};

}

#endif
