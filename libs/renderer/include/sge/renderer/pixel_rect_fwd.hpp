//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_RECT_FWD_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_RECT_FWD_HPP_INCLUDED

#include <sge/renderer/pixel_unit.hpp>
#include <fcppt/math/box/rect_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A typedef for a rect in pixel coordinates

\ingroup sge_renderer
*/
using
pixel_rect
=
fcppt::math::box::rect<
	sge::renderer::pixel_unit
>;

}
}

#endif
