//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge::opengl::context
{

using
optional_base_ref
=
fcppt::optional::reference<
	sge::opengl::context::base
>;

}

#endif
