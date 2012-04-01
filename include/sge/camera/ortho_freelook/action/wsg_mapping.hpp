#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_WSG_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_WSG_MAPPING_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>

namespace sge
{
namespace camera
{
namespace ortho_freelook
{
namespace action
{
/**
\brief Creates mapping where 'w' and 's' zoom in/out and 'g' activates the panning.
\ingroup sgecamera
*/
SGE_CAMERA_SYMBOL
action::mapping const
wsg_mapping();
}
}
}
}

#endif

