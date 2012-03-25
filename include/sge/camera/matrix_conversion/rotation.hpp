#ifndef SGE_CAMERA_MATRIX_CONVERSION_ROTATION_HPP_INCLUDED
#define SGE_CAMERA_MATRIX_CONVERSION_ROTATION_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/renderer/matrix4.hpp>


namespace sge
{
namespace camera
{
namespace matrix_conversion
{
SGE_CAMERA_SYMBOL
renderer::matrix4 const
rotation(
	camera::coordinate_system::object const &);
}
}
}

#endif

