//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PAN_SPEED_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PAN_SPEED_HPP_INCLUDED

#include <sge/renderer/vector2.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::camera::ortho_freelook
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector2,
	pan_speed
);

}

#endif
