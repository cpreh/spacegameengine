//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TARGET_BASE_HPP_INCLUDED
#define SGE_OPENGL_TARGET_BASE_HPP_INCLUDED

#include <sge/opengl/target/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::target
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base();

  virtual void bind() = 0;

  virtual void unbind() = 0;

  virtual void end_rendering() = 0;
};

}

#endif
