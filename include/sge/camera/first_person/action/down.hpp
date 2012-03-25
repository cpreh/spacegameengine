#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_DOWN_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_DOWN_HPP_INCLUDED

#include <sge/camera/first_person/action/optional_key_code.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace camera
{
namespace first_person
{
namespace action
{
/**
\brief The (optional) key code belonging to the action "go down"
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	action::optional_key_code,
	down);
}
}
}
}

#endif

