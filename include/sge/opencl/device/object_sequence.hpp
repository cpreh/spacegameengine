#ifndef SGE_OPENCL_DEVICE_OBJECT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_DEVICE_OBJECT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/device/object_fwd.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opencl
{
namespace device
{
typedef
boost::ptr_vector<opencl::device::object>
object_sequence;
}
}
}

#endif
