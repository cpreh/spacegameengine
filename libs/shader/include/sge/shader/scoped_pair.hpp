//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED
#define SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED

#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/shader/pair_fwd.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::shader
{

class scoped_pair
{
  FCPPT_NONMOVABLE(scoped_pair);

public:
  using pair_ref = fcppt::reference<sge::shader::pair>;

  SGE_SHADER_DETAIL_SYMBOL
  scoped_pair(sge::renderer::context::core_ref, pair_ref);

  SGE_SHADER_DETAIL_SYMBOL
  ~scoped_pair();

private:
  pair_ref const parent_;

  sge::renderer::cg::scoped_program scoped_vertex_program_;

  sge::renderer::cg::scoped_program scoped_pixel_program_;
};

}

#endif
