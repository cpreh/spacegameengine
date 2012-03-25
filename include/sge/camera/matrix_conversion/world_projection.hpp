#ifndef SGE_CAMERA_MATRIX_CONVERSION_WORLD_PROJECTION_HPP_INCLUDED
#define SGE_CAMERA_MATRIX_CONVERSION_WORLD_PROJECTION_HPP_INCLUDED

#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/renderer/matrix4.hpp>


namespace sge
{
namespace camera
{
namespace matrix_conversion
{
SGE_CAMERA_SYMBOL
renderer::matrix4 const
world_projection(
	camera::coordinate_system::object const &,
	camera::projection_matrix const &);
}
}
}

#endif

