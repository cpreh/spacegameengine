#ifndef SGE_CAMERA_FIRST_PERSON_MOVEMENT_SPEED_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_MOVEMENT_SPEED_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
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
	movement_speed);
}
}
}

#endif

