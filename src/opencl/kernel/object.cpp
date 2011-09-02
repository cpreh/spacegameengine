#include "../handle_error.hpp"
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/program/object.hpp>
#include <fcppt/text.hpp>

sge::opencl::kernel::object::object(
	program::object &_program,
	kernel::name const &_name)
:
	kernel_(0)
{
	cl_int error_code;

	clCreateKernel(
		_program.program_,
		_name.c_str(),
		&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateKernel"));
}

sge::opencl::kernel::object::~object()
{
	if(!kernel_)
		return;

	cl_int const error_code =
		clReleaseKernel(
			kernel_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseKernel"));
}
