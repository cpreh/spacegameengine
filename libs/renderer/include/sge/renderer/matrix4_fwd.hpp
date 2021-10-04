//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_MATRIX4_FWD_HPP_INCLUDED
#define SGE_RENDERER_MATRIX4_FWD_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/static_fwd.hpp>


namespace sge::renderer
{

/**
\brief A 4x4 matrix using renderer::scalar

\ingroup sge_renderer
*/
using
matrix4
=
fcppt::math::matrix::static_<
	sge::renderer::scalar,
	4,
	4
>;

}

#endif
