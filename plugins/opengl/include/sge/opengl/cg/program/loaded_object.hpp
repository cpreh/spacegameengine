//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::cg::program
{

class loaded_object : public sge::renderer::cg::loaded_program
{
  FCPPT_NONMOVABLE(loaded_object);

public:
  explicit loaded_object(sge::cg::program::object_ref);

  ~loaded_object() override;

  void activate() const;

  void deactivate() const;

private:
  sge::cg::program::object_ref const program_;
};

}

#endif
