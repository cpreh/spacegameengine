#ifndef SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED

#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/program/device_blob_map.hpp>
#include <sge/opencl/program/build_parameters_fwd.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <CL/cl.h>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
namespace program
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		context::object &,
		program::device_blob_map const &);

	SGE_OPENCL_SYMBOL explicit
	object(
		context::object &,
		program::source_string_sequence const &);

	SGE_OPENCL_SYMBOL cl_program
	impl() const;

	SGE_OPENCL_SYMBOL void
	build(
		program::build_parameters const &);

	SGE_OPENCL_SYMBOL program::device_blob_map const
	binaries() const;

	SGE_OPENCL_SYMBOL ~object();
private:
	friend class kernel::object;

	cl_program program_;
	program::notification_callback notification_callback_;

	static void
	notification_callback(
		cl_program,
		void *);
};
}
}
}

#endif
