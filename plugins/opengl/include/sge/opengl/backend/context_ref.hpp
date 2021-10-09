//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BACKEND_CONTEXT_REF_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_CONTEXT_REF_HPP_INCLUDED

#include <sge/opengl/backend/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::opengl::backend
{

using context_ref = fcppt::reference<sge::opengl::backend::context>;

}

#endif
