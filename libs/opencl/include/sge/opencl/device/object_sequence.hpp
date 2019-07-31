//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_DEVICE_OBJECT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_DEVICE_OBJECT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/device/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace device
{
typedef
std::vector<opencl::device::object>
object_sequence;
}
}
}

#endif
