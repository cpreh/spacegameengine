//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_ATTACHMENT_HPP_INCLUDED
#define SGE_OPENGL_FBO_ATTACHMENT_HPP_INCLUDED

#include <sge/opengl/fbo/attachment_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::fbo
{

class attachment
{
  FCPPT_NONMOVABLE(attachment);

protected:
  attachment();

public:
  virtual ~attachment();
};

}

#endif
