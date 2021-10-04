//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_CLIP_PLANE_AREA_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_CLIP_PLANE_AREA_FWD_HPP_INCLUDED

#include <sge/renderer/vector4_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sge::renderer::state::ffp::clip_plane
{

/**
\brief Describes a clip plane

A clip plane is a vector of four components, interpreted as a plane equation.
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector4,
	area
);

}

#endif
