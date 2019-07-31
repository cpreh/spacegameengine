//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/exception.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/kernel/local_buffer.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/program/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/variant/apply.hpp>


sge::opencl::kernel::object::object(
	program::object &_program,
	kernel::name const &_name)
:
	// TODO: change this to directly construct the elements via free functions
	name_(
		_name.get()),
	kernel_(
		nullptr),
	argument_count_()
{
	cl_int error_code;

	kernel_ =
		clCreateKernel(
			_program.program_,
			_name.get().c_str(),
			&error_code);

	if(error_code == CL_INVALID_KERNEL_NAME)
		throw
			sge::opencl::exception(
				FCPPT_TEXT("The kernel name \"")+
				fcppt::from_std_string(
					_name.get())+
				FCPPT_TEXT("\" is invalid."));

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateKernel"));

	error_code =
		clGetKernelInfo(
			kernel_,
			CL_KERNEL_NUM_ARGS,
			sizeof(cl_uint),
			&argument_count_,
			// Pointer to the argument size
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetKernelInfo(number of arguments)"));
}

sge::opencl::kernel::name::value_type
sge::opencl::kernel::object::name() const
{
	return name_;
}

cl_kernel
sge::opencl::kernel::object::impl()
{
	return kernel_;
}

void
sge::opencl::kernel::object::argument(
	kernel::argument_index const &index,
	memory_object::base &o)
{
	FCPPT_ASSERT_PRE_MESSAGE(
		index.get() < argument_count_,
		FCPPT_TEXT("Kernel argument index is out of range"));

	cl_mem mem_ptr = o.impl();

	cl_int const error_code =
		clSetKernelArg(
			kernel_,
			static_cast<cl_uint>(
				index.get()),
			sizeof(
				cl_mem),
			&mem_ptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg(memory object)"));
}

void
sge::opencl::kernel::object::argument(
	sge::opencl::kernel::argument_index const &_index,
	sge::opencl::kernel::numeric_type const &_object
)
{
	fcppt::variant::apply(
		[
			_index,
			this
		](
			auto const _value
		)
		{
			cl_int const error_code{
				::clSetKernelArg(
					kernel_,
					fcppt::cast::size<
						cl_uint
					>(
						_index.get()
					),
					sizeof(
						decltype(
							_value
						)
					),
					&_value
				)
			};

			switch(
				error_code
			)
			{
			case CL_SUCCESS:
				return;
			case CL_INVALID_ARG_SIZE:
				throw
					sge::opencl::exception{
						FCPPT_TEXT("Kernel \"")+
						fcppt::from_std_string(
							name_
						)
						+
						FCPPT_TEXT("\": clSetKernelArg for argument ")+
						fcppt::output_to_fcppt_string(
							_index
						)
						+
						FCPPT_TEXT(" returned CL_INVALID_ARG_SIZE. ")
						FCPPT_TEXT("This could mean that you mixed up the ordering or the exact types ")
						FCPPT_TEXT("of the kernel's arguments.")
					};
			}

			sge::opencl::impl::handle_error(
				error_code,
				FCPPT_TEXT("clSetKernelArg(numeric type)")
			);
		},
		_object
	);
}

void
sge::opencl::kernel::object::argument(
	kernel::argument_index const &index,
	unsigned char const * const _data,
	memory_object::byte_size const &_bytes)
{
	cl_int const error_code =
		clSetKernelArg(
			kernel_,
			static_cast<cl_uint>(
				index.get()),
			_bytes.get(),
			_data);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg(arbitrary data)"));
}

void
sge::opencl::kernel::object::argument(
	kernel::argument_index const &index,
	kernel::local_buffer const &_local_buffer)
{
	cl_int const error_code =
		clSetKernelArg(
			kernel_,
			static_cast<cl_uint>(
				index.get()),
			_local_buffer.byte_size(),
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg(local buffer)"));
}

std::size_t
sge::opencl::kernel::object::work_group_size(
	opencl::device::object &_device) const
{
	std::size_t result;

	cl_int const error_code =
		clGetKernelWorkGroupInfo(
			kernel_,
			_device.impl(),
			CL_KERNEL_WORK_GROUP_SIZE,
			sizeof(std::size_t),
			&result,
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetKernelWorkGroupInfo()"));

	return result;
}

sge::opencl::kernel::object::~object()
{
	if(!kernel_)
		return;

	cl_int const error_code =
		clReleaseKernel(
			kernel_);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseKernel"));
}
