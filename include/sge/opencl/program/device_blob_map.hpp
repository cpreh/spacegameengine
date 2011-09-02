#ifndef SGE_OPENCL_PROGRAM_BLOB_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BLOB_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/program/blob.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <vector>
#include <utility>

namespace sge
{
namespace opencl
{
namespace program
{
typedef
std::vector
<
	std::pair<device::object*,program::blob>
>
device_blob_map;
}
}
}

#endif
