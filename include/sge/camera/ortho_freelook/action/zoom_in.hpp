#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_ZOOM_IN_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_ZOOM_IN_HPP_INCLUDED

#include <sge/camera/ortho_freelook/action/optional_key_code.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace camera
{
namespace ortho_freelook
{
namespace action
{
/**
\brief The (optional) key code belonging to the action "zoom in"
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	action::optional_key_code,
	zoom_in);
}
}
}
}

#endif

