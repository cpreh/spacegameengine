//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_PIXEL_POS_FWD_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_POS_FWD_HPP_INCLUDED

#include <sge/renderer/pixel_unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sge::renderer
{

/**
\brief A typedef for a position in pixel coordinates

\ingroup sge_renderer
*/
using pixel_pos = fcppt::math::vector::static_<sge::renderer::pixel_unit, 2>;

}

#endif
