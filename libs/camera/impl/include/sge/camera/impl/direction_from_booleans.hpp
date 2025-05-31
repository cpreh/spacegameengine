#ifndef SGE_CAMERA_IMPL_DIRECTION_FROM_BOOLEANS_HPP_INCLUDED
#define SGE_CAMERA_IMPL_DIRECTION_FROM_BOOLEANS_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>

namespace sge::camera::impl
{
[[nodiscard]] sge::renderer::scalar direction_from_booleans(bool left, bool right);
}

#endif
