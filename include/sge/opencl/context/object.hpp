#ifndef SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>
#include <CL/cl.h>

namespace sge
{
namespace opencl
{
namespace context
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		context::parameters const &);

	SGE_OPENCL_SYMBOL cl_context
	impl() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	friend class opencl::platform::object;
	friend class opencl::command_queue::object;
	friend class opencl::program::object;

	cl_context context_;
	context::error_callback const error_callback_;


	static void
	error_callback(
		char const *,
		void const *,
		size_t,
		void *);
};
}
}
}

#endif
