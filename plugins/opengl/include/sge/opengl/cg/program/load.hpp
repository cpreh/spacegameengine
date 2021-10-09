//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CG_PROGRAM_LOAD_HPP_INCLUDED
#define SGE_OPENGL_CG_PROGRAM_LOAD_HPP_INCLUDED

#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>

namespace sge::opengl::cg::program
{

sge::renderer::cg::loaded_program_unique_ptr load(sge::cg::program::object_ref);

}

#endif
