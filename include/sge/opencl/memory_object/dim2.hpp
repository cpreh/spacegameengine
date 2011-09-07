#ifndef SGE_OPENCL_MEMORY_OBJECT_DIM2_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_DIM2_HPP_INCLUDED

#include <fcppt/math/dim/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
typedef
fcppt::math::dim::static_<std::size_t,2>::type
dim2;
}
}
}

#endif
