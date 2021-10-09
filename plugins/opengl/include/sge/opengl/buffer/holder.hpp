//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/opengl/buffer/base_ref.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::buffer
{

class holder
{
  FCPPT_NONMOVABLE(holder);

public:
  explicit holder(sge::opengl::buffer::base_ref);

  ~holder();

  [[nodiscard]] sge::opengl::buffer::id id() const;

private:
  sge::opengl::buffer::base_ref const base_;

  sge::opengl::buffer::id const id_;
};

}

#endif
