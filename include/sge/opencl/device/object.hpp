#ifndef SGE_OPENCL_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <ostream>
#include <CL/cl.h>

namespace sge
{
namespace opencl
{
namespace device
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL cl_device_id
	impl() const;

	SGE_OPENCL_SYMBOL void
	output_info(
		std::ostream &) const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	friend class opencl::platform::object;
	friend class opencl::context::object;
	friend class opencl::command_queue::object;
	friend class opencl::program::object;

	cl_device_id const device_id_;

	explicit
	object(
		cl_device_id const &);
};
}
}
}

#endif
