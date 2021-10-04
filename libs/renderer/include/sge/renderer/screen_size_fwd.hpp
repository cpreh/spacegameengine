//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_SCREEN_SIZE_FWD_HPP_INCLUDED
#define SGE_RENDERER_SCREEN_SIZE_FWD_HPP_INCLUDED

#include <sge/renderer/screen_unit.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sge::renderer
{

/**
\brief A typedef for a two dimensional renderer::screen_unit

\ingroup sge_renderer
*/
using
screen_size
=
fcppt::math::dim::static_<
	sge::renderer::screen_unit,
	2
>;

}

#endif
