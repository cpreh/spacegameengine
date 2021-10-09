//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_RENDER_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_FBO_RENDER_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::fbo
{

class render_buffer_holder
{
  FCPPT_NONMOVABLE(render_buffer_holder);

public:
  explicit render_buffer_holder(sge::opengl::fbo::const_config_ref);

  ~render_buffer_holder();

  [[nodiscard]] GLuint id() const;

private:
  sge::opengl::fbo::const_config_ref const context_;

  GLuint const id_;
};

}

#endif
