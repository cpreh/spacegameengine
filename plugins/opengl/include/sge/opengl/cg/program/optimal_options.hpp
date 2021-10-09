//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CG_PROGRAM_OPTIMAL_OPTIONS_HPP_INCLUDED
#define SGE_OPENGL_CG_PROGRAM_OPTIMAL_OPTIONS_HPP_INCLUDED

#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>

namespace sge::opengl::cg::program
{

sge::cg::program::compile_options
optimal_options(sge::cg::context::object const &, sge::cg::profile::object const &);

}

#endif
