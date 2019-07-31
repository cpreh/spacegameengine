//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/execution_mode_fwd.hpp>
#include <sge/opencl/command_queue/profiling_mode_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
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
	SGE_OPENCL_DETAIL_SYMBOL explicit
	object(
		opencl::device::object &,
		opencl::context::object &,
		command_queue::execution_mode,
		command_queue::profiling_mode);

	SGE_OPENCL_DETAIL_SYMBOL opencl::context::object &
	context() const;

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object &
	device() const;

	SGE_OPENCL_DETAIL_SYMBOL cl_command_queue
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL void
	finish();

	SGE_OPENCL_DETAIL_SYMBOL ~object();
private:
	opencl::context::object &context_;
	opencl::device::object &device_;
	cl_command_queue queue_;
};
}
}
}

#endif
