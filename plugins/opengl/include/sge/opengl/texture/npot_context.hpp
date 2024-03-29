//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_NPOT_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_NPOT_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/texture/npot_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class npot_context : public sge::opengl::context::base
{
  FCPPT_NONMOVABLE(npot_context);

public:
  using parameter = sge::opengl::info::context const &;

  explicit npot_context(sge::opengl::info::context const &);

  ~npot_context() override;

  [[nodiscard]] bool is_supported() const;

  static sge::opengl::context::id const static_id;

private:
  bool const is_supported_;
};

}

#endif
