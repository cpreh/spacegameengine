#ifndef SGE_CAMERA_COORDINATE_SYSTEM_FORWARD_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_FORWARD_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace camera
{
namespace coordinate_system
{
/**
\brief The forward axis of a coordinate system
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector3,
	forward);
}
}
}

#endif

