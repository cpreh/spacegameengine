#ifndef SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <fcppt/container/array_fwd.hpp>
#include <cstddef>

namespace sge
{
namespace opencl
{
namespace command_queue
{
template<std::size_t N>
SGE_OPENCL_SYMBOL void
enqueue_kernel(
	opencl::command_queue::object &,
	opencl::kernel::object &,
	fcppt::container::array<std::size_t,N> const &global_dim,
	fcppt::container::array<std::size_t,N> const &work_dim);
}
}
}

#endif
