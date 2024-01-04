//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_ffp_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge::renderer::context
{

using scoped_ffp_unique_ptr = fcppt::unique_ptr<sge::renderer::context::scoped_ffp>;

}

#endif
