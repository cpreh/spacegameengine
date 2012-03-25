#ifndef SGE_CAMERA_OPTIONAL_PROJECTION_MATRIX_HPP_INCLUDED
#define SGE_CAMERA_OPTIONAL_PROJECTION_MATRIX_HPP_INCLUDED

#include <sge/camera/projection_matrix.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sge
{
namespace camera
{
typedef
fcppt::optional<sge::camera::projection_matrix>
optional_projection_matrix;
}
}

#endif

