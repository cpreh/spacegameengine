//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_FBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/optional_config.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::fbo
{

class context : public sge::opengl::context::base
{
  FCPPT_NONMOVABLE(context);

public:
  using parameter = sge::opengl::info::context const &;

  explicit context(sge::opengl::info::context const &);

  ~context() override;

  [[nodiscard]] sge::opengl::fbo::optional_config const &config() const;

  static sge::opengl::context::id const static_id;

private:
  sge::opengl::fbo::optional_config config_;
};

}

#endif
