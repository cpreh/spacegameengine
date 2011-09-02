#include "../handle_error.hpp"
#include <sge/opencl/device/object.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/text.hpp>
#include <cstring>
#include <cstddef>
#include <CL/cl.h>

namespace
{
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
		FCPPT_TEXT("clGetDeviceInfo"));

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
		FCPPT_TEXT("clGetPlatformInfo"));

	Result result;
	std::memcpy(
		&result,
		result_string.data(),
		static_cast<std::size_t>(
			result_string.size()));
	return result;
}

std::string const
device_type_to_string(
	cl_device_type const dt)
{
	switch(dt)
	{
		case CL_DEVICE_TYPE_CPU: return "CL_DEVICE_TYPE_CPU";
		case CL_DEVICE_TYPE_GPU: return "CL_DEVICE_TYPE_GPU";
		case CL_DEVICE_TYPE_ACCELERATOR: return "CL_DEVICE_TYPE_ACCELERATOR";
		case CL_DEVICE_TYPE_DEFAULT: return "CL_DEVICE_TYPE_DEFAULT";
		case CL_DEVICE_TYPE_ALL: return "CL_DEVICE_TYPE_ALL";
		default: return "UNKNOWN";
	}
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
	cl_device_type const dt =
		device_info<cl_device_type>(
			device_id_,
			CL_DEVICE_TYPE);

	s << "CL_DEVICE_TYPE: " << device_type_to_string(dt) << "\n";

	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VENDOR_ID,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_COMPUTE_UNITS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,cl_uint);
	// Returns a size_t[CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS]
	//SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_MAX_WORK_ITEM_SIZES,size_t[]);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_GROUP_SIZE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CLOCK_FREQUENCY,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ADDRESS_BITS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_MEM_ALLOC_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE_SUPPORT,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_READ_IMAGE_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WRITE_IMAGE_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_WIDTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_HEIGHT,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_WIDTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_HEIGHT,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_DEPTH,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_SAMPLERS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_PARAMETER_SIZE,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MEM_BASE_ADDR_ALIGN,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,cl_ulong);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_ARGS,cl_uint);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ERROR_CORRECTION_SUPPORT,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_HOST_UNIFIED_MEMORY,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PROFILING_TIMER_RESOLUTION,size_t);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ENDIAN_LITTLE,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_AVAILABLE,cl_bool);
	SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_COMPILER_AVAILABLE,cl_bool);
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
