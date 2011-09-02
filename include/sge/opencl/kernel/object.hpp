#ifndef SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED

#include <sge/opencl/kernel/name.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <CL/cl.h>

namespace sge
{
namespace opencl
{
namespace kernel
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	explicit
	object(
		program::object &,
		kernel::name const &);

	~object();
private:
	cl_kernel kernel_;
};
}
}
}

#endif
