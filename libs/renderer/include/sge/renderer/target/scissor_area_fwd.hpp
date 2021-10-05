//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_SCISSOR_AREA_FWD_HPP_INCLUDED
#define SGE_RENDERER_TARGET_SCISSOR_AREA_FWD_HPP_INCLUDED

#include <sge/renderer/pixel_rect_fwd.hpp>
#include <fcppt/declare_strong_typedef.hpp>


namespace sge::renderer::target
{

/**
 * \brief A strong typedef to a pixel rect describing a scissor area
*/
FCPPT_DECLARE_STRONG_TYPEDEF(
	sge::renderer::pixel_rect,
	scissor_area
);

}

#endif
