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


#include "../handle_error.hpp"
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/clinclude.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/next_prior.hpp>
// This is needed to get the CL_DEVICE_HALF_FP_CONFIG macro. However,
// clGetDeviceInfo still fails when including and using this.
//#include <CL/cl_ext.h>
#include <cstring>
#include <cstddef>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace
{
template<typename Source,typename Dest>
typename
boost::enable_if
<
	boost::is_same
	<
		Dest,
		std::string
	>,
	void
>::type
copy_to_result(
	Source const &s,
	Dest &d)
{
	d.resize(
		static_cast<typename Dest::size_type>(
			s.size()-1));

	std::copy(
		s.begin(),
		s.end(),
		d.begin());
}

template<typename Source,typename Dest>
typename
boost::disable_if
<
	boost::is_same
	<
		Dest,
		std::string
	>,
	void
>::type
copy_to_result(
	Source const &s,
	Dest &d)
{
	std::memcpy(
		&d,
		s.data(),
		static_cast<std::size_t>(
			s.size()));
}

template<typename Result>
Result const
device_info(
	cl_device_id const &current_device,
	cl_device_info const &info)
{
	size_t param_value_size;

	cl_int error_code =
		clGetDeviceInfo(
			current_device,
			info,
			0, // param value size (we don't know that, yet)
			0, // param value (we don't want that, yet)
			&param_value_size);

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceInfo(option size)"));

	fcppt::container::raw_vector<char> result_string(
		static_cast<fcppt::container::raw_vector<char>::size_type>(
			param_value_size));

	error_code =
		clGetDeviceInfo(
			current_device,
			info,
			param_value_size,
			result_string.data(),
			// param value size
			0);

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceInfo(option value)"));

	Result result;

	copy_to_result(
		result_string,
		result);

	return result;
}


#define SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(constant) case constant: return #constant

std::string const
device_type_to_string(
	cl_device_type const dt)
{
	switch(
		dt)
	{
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_DEVICE_TYPE_CPU);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_DEVICE_TYPE_GPU);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_DEVICE_TYPE_ACCELERATOR);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_DEVICE_TYPE_DEFAULT);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_DEVICE_TYPE_ALL);
	}
	FCPPT_ASSERT_UNREACHABLE;
}

std::string const
device_fp_config_to_string(
	cl_device_fp_config const dt)
{
	std::string result;

	if(dt & CL_FP_DENORM)
		result += "CL_FP_DENORM";
	if(dt & CL_FP_DENORM && dt & CL_FP_INF_NAN)
		result += ", ";
	if(dt &  CL_FP_INF_NAN)
		result += "CL_FP_INF_NAN";

	if(dt & CL_FP_INF_NAN && dt & CL_FP_ROUND_TO_NEAREST)
		result += ", ";
	if(dt & CL_FP_ROUND_TO_NEAREST)
		result += "CL_FP_ROUND_TO_NEAREST";

	if(dt & CL_FP_ROUND_TO_NEAREST && dt & CL_FP_ROUND_TO_ZERO)
		result += ", ";
	if(dt & CL_FP_ROUND_TO_ZERO)
		result += "CL_FP_ROUND_TO_ZERO";

	if(dt & CL_FP_ROUND_TO_ZERO && dt & CL_FP_ROUND_TO_INF)
		result += ", ";
	if(dt & CL_FP_ROUND_TO_INF)
		result += "CL_FP_ROUND_TO_INF";

	if(dt & CL_FP_ROUND_TO_INF && dt & CL_FP_FMA)
		result += ", ";
	if(dt & CL_FP_FMA)
		result += "CL_FP_FMA";

	return result;
}

std::string const
device_exec_capabilities_to_string(
	cl_device_exec_capabilities const dt)
{
	std::string result;

	if(dt & CL_EXEC_KERNEL)
		result += "CL_EXEC_KERNEL";

	if(dt & CL_EXEC_KERNEL && dt & CL_EXEC_NATIVE_KERNEL)
		result += ", ";

	if(dt & CL_EXEC_NATIVE_KERNEL)
		result += "CL_EXEC_NATIVE_KERNEL";

	return result;
}

std::string const
device_mem_cache_type_to_string(
	cl_device_mem_cache_type const dt)
{
	switch(
		dt)
	{
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_NONE);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_READ_ONLY_CACHE);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_READ_WRITE_CACHE);
	}
	FCPPT_ASSERT_UNREACHABLE;
}

std::string const
device_local_mem_type_to_string(
	cl_device_local_mem_type const dt)
{
	switch(
		dt)
	{
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_LOCAL);
		SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(
			CL_GLOBAL);
	}
	FCPPT_ASSERT_UNREACHABLE;
}

std::string const
command_queue_properties_to_string(
	cl_command_queue_properties const dt)
{
	std::string result;

	if(dt & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
		result += "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE";

	if(dt & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE && dt & CL_QUEUE_PROFILING_ENABLE)
		result += ", ";

	if(dt & CL_QUEUE_PROFILING_ENABLE)
		result += "CL_QUEUE_PROFILING_ENABLE";

	return result;
}

std::string
max_work_item_sizes_to_string(
	cl_device_id const device)
{
	cl_uint const max_work_item_dimensions =
		device_info<cl_uint>(
			device,
			CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);

	typedef
	fcppt::container::raw_vector<std::size_t>
	size_vector;

	size_vector sizes(
		static_cast<size_vector::size_type>(
			max_work_item_dimensions));

	cl_int const error_code =
		clGetDeviceInfo(
			device,
			CL_DEVICE_MAX_WORK_ITEM_SIZES,
			static_cast<std::size_t>(
				sizeof(std::size_t) * max_work_item_dimensions),
			sizes.data(),
			// param value size
			0);

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceInfo(option value)"));

	std::string result;
	result += '(';
	for(size_vector::const_iterator it = sizes.begin(); it != sizes.end(); ++it)
	{
		result +=
			fcppt::insert_to_std_string(
				*it);

		if(it != boost::prior(sizes.end()))
			result += ", ";
	}
	result += ')';

	return result;
}
}

#define SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(name,type)\
	s << #name << ": " << device_info<type>(device_id_,name) << "\n"

cl_device_id
sge::opencl::device::object::impl() const
{
	return device_id_;
}

void
sge::opencl::device::object::output_info(
	std::ostream &s) const
{

	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ADDRESS_BITS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_AVAILABLE,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_COMPILER_AVAILABLE,cl_bool);
	s
		<< "CL_DEVICE_DOUBLE_FP_CONFIG: "
		<<
			device_fp_config_to_string(
				device_info<cl_device_fp_config>(
					device_id_,
					CL_DEVICE_TYPE))
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ENDIAN_LITTLE,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ERROR_CORRECTION_SUPPORT,cl_bool);
	s
		<< "CL_DEVICE_EXECUTION_CAPABILITIES: "
		<<
			device_exec_capabilities_to_string(
				device_info<cl_device_exec_capabilities>(
					device_id_,
					CL_DEVICE_EXECUTION_CAPABILITIES))
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_EXTENSIONS,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,cl_ulong);
	s
		<< "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE: "
		<<
			device_mem_cache_type_to_string(
				device_info<cl_device_mem_cache_type>(
					device_id_,
					CL_DEVICE_GLOBAL_MEM_CACHE_TYPE))
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_SIZE,cl_ulong);
	/*
	s
		<< "CL_DEVICE_HALF_FP_CONFIG: "
		<<
			device_fp_config_to_string(
				device_info<cl_device_fp_config>(
					device_id_,
					CL_DEVICE_HALF_FP_CONFIG))
		<< "\n";
	*/
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE_SUPPORT,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_HEIGHT,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_WIDTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_DEPTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_HEIGHT,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_WIDTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_LOCAL_MEM_SIZE,cl_ulong);
	s
		<< "CL_DEVICE_LOCAL_MEM_TYPE: "
		<<
			device_local_mem_type_to_string(
				device_info<cl_device_local_mem_type>(
					device_id_,
					CL_DEVICE_LOCAL_MEM_TYPE))
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CLOCK_FREQUENCY,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_COMPUTE_UNITS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_MEM_ALLOC_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_PARAMETER_SIZE,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_READ_IMAGE_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_SAMPLERS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_GROUP_SIZE,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,cl_uint);
	s
		<< "CL_DEVICE_MAX_WORK_ITEM_SIZES: "
		<<
			max_work_item_sizes_to_string(
				device_id_)
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WRITE_IMAGE_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MEM_BASE_ADDR_ALIGN,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NAME,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PROFILE,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PROFILING_TIMER_RESOLUTION,size_t);
	s
		<< "CL_DEVICE_QUEUE_PROPERTIES: "
		<<
			command_queue_properties_to_string(
				device_info<cl_command_queue_properties>(
					device_id_,
					CL_DEVICE_QUEUE_PROPERTIES))
		<< "\n";
	s
		<< "CL_DEVICE_SINGLE_FP_CONFIG: "
		<<
			device_fp_config_to_string(
				device_info<cl_device_fp_config>(
					device_id_,
					CL_DEVICE_SINGLE_FP_CONFIG))
		<< "\n";
	s
		<< "CL_DEVICE_TYPE: "
		<<
			device_type_to_string(
				device_info<cl_device_type>(
					device_id_,
					CL_DEVICE_TYPE))
		<< "\n";
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VENDOR,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VENDOR_ID,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VERSION,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DRIVER_VERSION,std::string);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_HOST_UNIFIED_MEMORY,cl_bool);
}

sge::opencl::device::object::~object()
{
}

sge::opencl::device::object::object(
	cl_device_id const &_device_id)
:
	device_id_(
		_device_id)
{
}
