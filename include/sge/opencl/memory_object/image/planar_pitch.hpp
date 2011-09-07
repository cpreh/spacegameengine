#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_PITCH_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_PITCH_HPP_INCLUDED

#include <sge/opencl/memory_object/dim2.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
FCPPT_MAKE_STRONG_TYPEDEF(
	dim2::value_type,
	planar_pitch);
}
}
}
}

#endif
