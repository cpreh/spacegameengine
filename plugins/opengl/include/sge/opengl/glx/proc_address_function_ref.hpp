//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_PROC_ADDRESS_FUNCTION_REF_HPP_INCLUDED
#define SGE_OPENGL_GLX_PROC_ADDRESS_FUNCTION_REF_HPP_INCLUDED

#include <sge/opengl/glx/proc_address_function.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::opengl::glx
{

using
proc_address_function_ref
=
fcppt::reference<
	sge::opengl::glx::proc_address_function
>;

}

#endif
