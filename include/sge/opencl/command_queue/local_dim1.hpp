#ifndef SGE_OPENCL_COMMAND_QUEUE_LOCAL_DIM1_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_LOCAL_DIM1_HPP_INCLUDED

#include <sge/opencl/dim1.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::opencl::dim1,
	local_dim1);
}
}
}

#endif

