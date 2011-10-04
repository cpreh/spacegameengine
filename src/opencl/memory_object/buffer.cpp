#include "to_opencl_mem_flags.hpp"
#include "../handle_error.hpp"
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/opencl/context/object.hpp>
#include <fcppt/text.hpp>

sge::opencl::memory_object::buffer::buffer(
	opencl::context::object &_context,
	memory_object::flags_field const &_flags,
	memory_object::byte_size const &_byte_size)
:
	impl_(0)
{
	cl_int error_code;
	impl_ = 
		clCreateBuffer(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_flags),
			_byte_size.get(),
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateBuffer"));
}

cl_mem
sge::opencl::memory_object::buffer::impl()
{
	return impl_;
}

sge::opencl::memory_object::buffer::~buffer()
{
	if(!impl_)
		return;

	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(buffer)"));
}
