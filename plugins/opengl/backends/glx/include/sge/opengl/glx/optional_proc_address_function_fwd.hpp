//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_GLX_OPTIONAL_PROC_ADDRESS_FUNCTION_FWD_HPP_INCLUDED
#define SGE_OPENGL_GLX_OPTIONAL_PROC_ADDRESS_FUNCTION_FWD_HPP_INCLUDED

#include <sge/opengl/glx/proc_address_function.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sge::opengl::glx
{

using optional_proc_address_function =
    fcppt::optional::reference<sge::opengl::glx::proc_address_function>;

}

#endif
