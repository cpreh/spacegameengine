//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_DECLARATION_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_DECLARATION_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::renderer::vertex
{

/**
\brief A unique pointer to an sge::renderer::vertex::declaration
*/
using
declaration_unique_ptr
=
fcppt::unique_ptr<
	sge::renderer::vertex::declaration
>;

}

#endif
