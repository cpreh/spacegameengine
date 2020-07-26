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
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/device/object_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	object(
		sge::opencl::device::object_ref,
		sge::opencl::context::object_ref,
		sge::opencl::command_queue::execution_mode,
		sge::opencl::command_queue::profiling_mode
	);

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::object &
	context() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::device::object &
	device() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	cl_command_queue
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL
	void
	finish();

	SGE_OPENCL_DETAIL_SYMBOL
	~object();
private:
	sge::opencl::context::object_ref const context_;
	sge::opencl::device::object_ref const device_;
	cl_command_queue queue_;
};

}
}
}

#endif
