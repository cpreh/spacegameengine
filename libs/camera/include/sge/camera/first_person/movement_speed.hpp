//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_MOVEMENT_SPEED_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_MOVEMENT_SPEED_HPP_INCLUDED

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
\brief The movement speed scaling
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::scalar,
	movement_speed
);

}
}
}

#endif
