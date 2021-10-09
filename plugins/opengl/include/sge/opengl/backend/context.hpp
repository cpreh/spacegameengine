//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BACKEND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context_fwd.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::backend
{

class context
{
  FCPPT_NONMOVABLE(context);

protected:
  context();

public:
  virtual ~context();

  [[nodiscard]] virtual sge::opengl::backend::current_unique_ptr activate() = 0;

  virtual void deactivate(sge::opengl::backend::current_unique_ptr &&) = 0;
};

}

#endif
