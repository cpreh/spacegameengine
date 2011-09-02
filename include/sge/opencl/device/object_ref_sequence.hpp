#ifndef SGE_OPENCL_DEVICE_OBJECT_REF_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_DEVICE_OBJECT_REF_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/device/object_fwd.hpp>
#include <vector>

namespace sge
{
namespace opencl
{
namespace device
{
typedef
std::vector<opencl::device::object *>
object_ref_sequence;
}
}
}

#endif
