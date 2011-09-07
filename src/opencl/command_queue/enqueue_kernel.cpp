#include "../handle_error.hpp"
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>

template<std::size_t N>
void
sge::opencl::command_queue::enqueue_kernel(
	command_queue::object &_queue,
	kernel::object &_kernel,
	fcppt::container::array<std::size_t,N> const &global_dim,
	fcppt::container::array<std::size_t,N> const &work_dim)
{
	cl_int const error_code =
		clEnqueueNDRangeKernel(
			_queue.impl(),
			_kernel.impl(),
			static_cast<cl_uint>(
				N),
			0, // global work offset (not implemented in 1.1)
			global_dim.data(),
			work_dim.data(),
			0,
			0,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel"));
}

template void sge::opencl::command_queue::enqueue_kernel<1>(
	command_queue::object &_queue,
	kernel::object &,
	fcppt::container::array<std::size_t,1> const &,
	fcppt::container::array<std::size_t,1> const &);

template void sge::opencl::command_queue::enqueue_kernel<2>(
	command_queue::object &_queue,
	kernel::object &,
	fcppt::container::array<std::size_t,2> const &,
	fcppt::container::array<std::size_t,2> const &);

template void sge::opencl::command_queue::enqueue_kernel<3>(
	command_queue::object &_queue,
	kernel::object &,
	fcppt::container::array<std::size_t,3> const &,
	fcppt::container::array<std::size_t,3> const &);
