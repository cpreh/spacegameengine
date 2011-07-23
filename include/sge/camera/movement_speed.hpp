#ifndef SGE_CAMERA_MOVEMENT_SPEED_HPP_INCLUDED
#define SGE_CAMERA_MOVEMENT_SPEED_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/make_strong_typedef.hpp>

namespace sge
{
namespace camera
{
FCPPT_MAKE_STRONG_TYPEDEF(
	renderer::scalar,
	movement_speed);
}
}

#endif
