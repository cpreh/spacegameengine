//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_HOLDER_HPP_INCLUDED

#include <sge/opengl/texture/id.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class holder
{
  FCPPT_NONMOVABLE(holder);

public:
  holder();

  ~holder();

  [[nodiscard]] sge::opengl::texture::id id() const;

private:
  sge::opengl::texture::id const id_;
};

}

#endif
