//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CONTEXT_SCOPED_CORE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_CORE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_core_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::renderer::context
{

using
scoped_core_unique_ptr
=
fcppt::unique_ptr<
	sge::renderer::context::scoped_core
>;

}

#endif
