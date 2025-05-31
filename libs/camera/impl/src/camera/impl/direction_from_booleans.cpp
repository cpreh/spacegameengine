#include <sge/camera/impl/direction_from_booleans.hpp>
#include <sge/renderer/scalar.hpp>

sge::renderer::scalar
sge::camera::impl::direction_from_booleans(bool const _left, bool const _right)
{
  if (_left && !_right)
  {
    return -1.0F;
  }

  if (_right && !_left)
  {
    return 1.0F;
  }

  return 0.0F;
}
