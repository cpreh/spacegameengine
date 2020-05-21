//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_CONST_OPTIONAL_DECLARATION_REF_FWD_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CONST_OPTIONAL_DECLARATION_REF_FWD_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief An optional sge::renderer::vertex::declaration reference

\see sge::renderer::device::vertex_declaration
*/
using
const_optional_declaration_ref
=
fcppt::optional::reference<
	sge::renderer::vertex::declaration const
>;

}
}
}

#endif
