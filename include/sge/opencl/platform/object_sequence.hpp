#ifndef SGE_OPENCL_PLATFORM_OBJECT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_OBJECT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/platform/object_fwd.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opencl
{
namespace platform
{
typedef
boost::ptr_vector<platform::object>
object_sequence;
}
}
}

#endif
