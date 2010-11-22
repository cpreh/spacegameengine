#ifndef SGE_CAMERA_PROJECTION_TO_MATRIX_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_TO_MATRIX_HPP_INCLUDED

#include <sge/camera/projection/object.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace camera
{
namespace projection
{
renderer::matrix4 const
to_matrix(
	object const &);
}
}
}

#endif
