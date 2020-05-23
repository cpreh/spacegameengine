//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OPTIONAL_MATRIX4_FWD_HPP_INCLUDED
#define SGE_RENDERER_OPTIONAL_MATRIX4_FWD_HPP_INCLUDED

#include <sge/renderer/matrix4_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
\brief An optional matrix4

\ingroup sge_renderer
*/
using
optional_matrix4
=
fcppt::optional::object<
	sge::renderer::matrix4
>;

}
}

#endif
