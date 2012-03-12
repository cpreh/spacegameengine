#ifndef SGE_OPENCL_MEMORY_OBJECT_VECTOR1_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_VECTOR1_HPP_INCLUDED

#include <sge/opencl/memory_object/size_type.hpp>
#include <fcppt/math/vector/static.hpp>
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
fcppt::math::vector::static_<memory_object::size_type,1>::type
vector1;
}
}
}

#endif

