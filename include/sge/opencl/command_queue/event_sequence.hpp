#ifndef SGE_OPENCL_COMMAND_QUEUE_EVENT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_EVENT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <fcppt/container/raw_vector_fwd.hpp>

namespace sge
{
namespace opencl
{
namespace command_queue
{
// This could be a set, too, but we usually want to use this to pass it to
// functions which expect a contiguous block of memory. That isn't the case
// with a set.
typedef
fcppt::container::raw_vector<cl_event>
event_sequence;
}
}
}

#endif

