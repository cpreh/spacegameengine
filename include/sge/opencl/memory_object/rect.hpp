#ifndef SGE_OPENCL_MEMORY_OBJECT_RECT_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_RECT_HPP_INCLUDED

#include <fcppt/math/box/basic_fwd.hpp>
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
fcppt::math::box::basic<std::size_t,2>
rect;
}
}
}

#endif
