//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_POSITION_FWD_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_POSITION_FWD_HPP_INCLUDED

#include <sge/renderer/vector3_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sge::renderer::state::ffp::lighting::light
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector3,
	position
);

}

#endif
