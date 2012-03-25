#ifndef SGE_CAMERA_PROJECTION_MATRIX_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_MATRIX_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace camera
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::matrix4,
	projection_matrix);
}
}

#endif

