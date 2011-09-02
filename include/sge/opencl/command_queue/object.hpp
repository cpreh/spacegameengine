#ifndef SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
namespace command_queue
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		opencl::device::object &,
		opencl::context::object &,
		command_queue::execution_mode::type,
		command_queue::profiling_mode::type);

	SGE_OPENCL_SYMBOL cl_command_queue
	impl() const;

	SGE_OPENCL_SYMBOL ~object();
private:
	cl_command_queue queue_;
};
}
}
}

#endif
