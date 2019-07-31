//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_MOUSE_SPEED_MULTIPLIER_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_MOUSE_SPEED_MULTIPLIER_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{

/**
\brief The scaling factor for the raw mouse event axis values
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::scalar,
	mouse_speed_multiplier
);

}
}
}

#endif
