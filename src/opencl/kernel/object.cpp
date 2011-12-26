/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/exception.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::opencl::kernel::object::object(
	program::object &_program,
	kernel::name const &_name)
:
	name_(
		_name.get()),
	kernel_(0)
{
	cl_int error_code;

	kernel_ =
		clCreateKernel(
			_program.program_,
			_name.get().c_str(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateKernel"));

	error_code =
		clGetKernelInfo(
			kernel_,
			CL_KERNEL_NUM_ARGS,
			sizeof(cl_uint),
			&argument_count_,
			// Pointer to the argument size
			0);

	opencl::handle_error(
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

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg(memory object)"));
}

namespace
{
struct numeric_visitor
{
FCPPT_NONASSIGNABLE(
	numeric_visitor);
public:
	typedef
	void
	result_type;

	explicit
	numeric_visitor(
		sge::opencl::kernel::name::value_type const &_name,
		cl_kernel const &_kernel,
		sge::opencl::kernel::argument_index const &_index)
	:
		name_(
			_name),
		kernel_(
			_kernel),
		index_(
			_index)
	{
	}

	template<typename T>
	result_type
	operator()(
		T const &t) const
	{
		cl_int const error_code =
			clSetKernelArg(
				kernel_,
				static_cast<cl_uint>(
					index_.get()),
				sizeof(
					T),
				&t);

		if(error_code == CL_SUCCESS)
			return;

		if(error_code == CL_INVALID_ARG_SIZE)
			throw sge::exception(
				FCPPT_TEXT("Kernel \"")+
				fcppt::from_std_string(
					name_)+
				FCPPT_TEXT("\": clSetKernelArg for argument ")+
				fcppt::insert_to_fcppt_string(
					index_)+
				FCPPT_TEXT(" returned CL_INVALID_ARG_SIZE. ")
				FCPPT_TEXT("This could mean that you mixed up the ordering or the exact types ")
				FCPPT_TEXT("of the kernel's arguments."));
		sge::opencl::handle_error(
			error_code,
			FCPPT_TEXT("clSetKernelArg(numeric type)"));
	}
private:
	sge::opencl::kernel::name::value_type const name_;
	cl_kernel const &kernel_;
	sge::opencl::kernel::argument_index const index_;
};
}

void
sge::opencl::kernel::object::argument(
	kernel::argument_index const &index,
	kernel::numeric_type const &o)
{
	fcppt::variant::apply_unary(
		numeric_visitor(
			name_,
			kernel_,
			index),
		o);
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

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clSetKernelArg(arbitrary data)"));
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
			0);

	opencl::handle_error(
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

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseKernel"));
}
