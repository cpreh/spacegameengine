//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_CONFIG_HPP_INCLUDED

#include <sge/opengl/ext.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config_fwd.hpp> // IWYU pragma: keep

namespace sge::opengl::state::core::depth_stencil::stencil
{

class config
{
public:
  using gl_stencil_func_separate = sge::opengl::fun_ref<PFNGLSTENCILFUNCSEPARATEPROC>;

  using gl_stencil_op_separate = sge::opengl::fun_ref<PFNGLSTENCILOPSEPARATEPROC>;

  config(gl_stencil_func_separate, gl_stencil_op_separate);

  [[nodiscard]] gl_stencil_func_separate stencil_func_separate() const;

  [[nodiscard]] gl_stencil_op_separate stencil_op_separate() const;

private:
  gl_stencil_func_separate stencil_func_separate_;

  gl_stencil_op_separate stencil_op_separate_;
};

}

#endif
