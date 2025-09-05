//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/exception.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/buffer/object.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <ostream>
#include <string>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace
{

using buffer_type = fcppt::container::buffer::object<char>;

template <typename Dest>
[[nodiscard]] std::string copy_to_result(buffer_type const &_source)
  requires(std::is_same_v<Dest, std::string>)
{
  return std::string(_source.begin(), std::prev(_source.end()));
}

template <typename Dest>
[[nodiscard]] Dest copy_to_result(buffer_type const &_source)
  requires(std::is_fundamental_v<Dest>)
{
  Dest dest{};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(&dest, _source.read_data(), _source.read_size());
FCPPT_PP_POP_WARNING

  return dest;
}

template <typename Result>
Result device_info(cl_device_id const &current_device, cl_device_info const &info)
{
  size_t param_value_size{};

  cl_int error_code = clGetDeviceInfo(
      current_device,
      info,
      0, // param value size (we don't know that, yet)
      nullptr, // param value (we don't want that, yet)
      &param_value_size);

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetDeviceInfo(option size)"));

  buffer_type result_string(fcppt::cast::size<buffer_type::size_type>(param_value_size));

  error_code = clGetDeviceInfo(
      current_device,
      info,
      param_value_size,
      result_string.write_data(),
      // param value size
      nullptr);

  result_string.written(result_string.write_size());

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetDeviceInfo(option value)"));

  return copy_to_result<Result>(result_string);
}

#define SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(constant) \
  case constant: \
    return #constant

std::string device_type_to_string(cl_device_type const dt)
{
  switch ( // NOLINT(hicpp-multiway-paths-covered)
      dt)
  {
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_DEVICE_TYPE_CPU); // NOLINT(hicpp-signed-bitwise)
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_DEVICE_TYPE_GPU); // NOLINT(hicpp-signed-bitwise)
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_DEVICE_TYPE_ACCELERATOR); // NOLINT(hicpp-signed-bitwise)
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_DEVICE_TYPE_DEFAULT); // NOLINT(hicpp-signed-bitwise)
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_DEVICE_TYPE_ALL); // NOLINT(hicpp-signed-bitwise)
    default: break;
  }
  throw sge::opencl::exception{FCPPT_TEXT("Invalid cl_device_type!")};
}

std::string device_fp_config_to_string(cl_device_fp_config const dt)
{
  std::string result;

  if ((dt & CL_FP_DENORM) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_DENORM";
  }
  if ((dt & CL_FP_DENORM) != 0 && (dt & CL_FP_INF_NAN) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }
  if ((dt & CL_FP_INF_NAN) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_INF_NAN";
  }
  if ((dt & CL_FP_INF_NAN) != 0 &&
      (dt & CL_FP_ROUND_TO_NEAREST) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }
  if ((dt & CL_FP_ROUND_TO_NEAREST) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_ROUND_TO_NEAREST";
  }
  if ((dt & CL_FP_ROUND_TO_NEAREST) != 0 &&
      (dt & CL_FP_ROUND_TO_ZERO) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }
  if ((dt & CL_FP_ROUND_TO_ZERO) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_ROUND_TO_ZERO";
  }
  if ((dt & CL_FP_ROUND_TO_ZERO) != 0 &&
      (dt & CL_FP_ROUND_TO_INF) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }
  if ((dt & CL_FP_ROUND_TO_INF) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_ROUND_TO_INF";
  }
  if ((dt & CL_FP_ROUND_TO_INF) != 0 && (dt & CL_FP_FMA) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }
  if ((dt & CL_FP_FMA) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_FP_FMA";
  }

  return result;
}

std::string device_exec_capabilities_to_string(cl_device_exec_capabilities const dt)
{
  std::string result;

  if ((dt & CL_EXEC_KERNEL) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_EXEC_KERNEL";
  }

  if ((dt & CL_EXEC_KERNEL) != 0 &&
      (dt & CL_EXEC_NATIVE_KERNEL) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }

  if ((dt & CL_EXEC_NATIVE_KERNEL) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_EXEC_NATIVE_KERNEL";
  }

  return result;
}

std::string device_mem_cache_type_to_string(cl_device_mem_cache_type const dt)
{
  switch ( // NOLINT(hicpp-multiway-paths-covered)
      dt)
  {
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_NONE);
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_READ_ONLY_CACHE);
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_READ_WRITE_CACHE);
    default: break;
  }
  throw sge::opencl::exception{FCPPT_TEXT("Invalid cl_device_mem_cache_type!")};
}

std::string device_local_mem_type_to_string(cl_device_local_mem_type const dt)
{
  switch ( // NOLINT(hicpp-multiway-paths-covered)
      dt)
  {
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_LOCAL);
    SGE_OPENCL_DEVICE_OUTPUT_CONSTANT(CL_GLOBAL);
    default: break;
  }
  throw sge::opencl::exception{FCPPT_TEXT("Invalid cl_device_local_mem_type!")};
}

std::string command_queue_properties_to_string(cl_command_queue_properties const dt)
{
  std::string result;

  if ((dt & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE";
  }

  if ((dt & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) != 0 &&
      (dt & CL_QUEUE_PROFILING_ENABLE) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += ", ";
  }

  if ((dt & CL_QUEUE_PROFILING_ENABLE) != 0) // NOLINT(hicpp-signed-bitwise)
  {
    result += "CL_QUEUE_PROFILING_ENABLE";
  }

  return result;
}

std::string max_work_item_sizes_to_string(cl_device_id const device // NOLINT(misc-misplaced-const)
)
{
  auto const max_work_item_dimensions =
      device_info<cl_uint>(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);

  using size_vector = fcppt::container::buffer::object<std::size_t>;

  size_vector sizes{fcppt::cast::size<size_vector::size_type>(max_work_item_dimensions)};

  cl_int const error_code = clGetDeviceInfo(
      device,
      CL_DEVICE_MAX_WORK_ITEM_SIZES,
      static_cast<std::size_t>(sizeof(std::size_t) * max_work_item_dimensions),
      sizes.write_data(),
      // param value size
      nullptr);

  sizes.written(sizes.write_size());

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetDeviceInfo(option value)"));

  return fcppt::output_to_std_string(fcppt::container::output(sizes));
}
}

#define SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(name, type) \
  s << #name << ": " << device_info<type>(device_id_, name) << "\n"

cl_device_id sge::opencl::device::object::impl() const { return device_id_; }

void sge::opencl::device::object::output_info(std::ostream &s) const
{
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ADDRESS_BITS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_AVAILABLE, cl_bool);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_COMPILER_AVAILABLE, cl_bool);
  s << "CL_DEVICE_DOUBLE_FP_CONFIG: "
    << device_fp_config_to_string(device_info<cl_device_fp_config>(device_id_, CL_DEVICE_TYPE))
    << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ENDIAN_LITTLE, cl_bool);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_ERROR_CORRECTION_SUPPORT, cl_bool);
  s << "CL_DEVICE_EXECUTION_CAPABILITIES: "
    << device_exec_capabilities_to_string(
           device_info<cl_device_exec_capabilities>(device_id_, CL_DEVICE_EXECUTION_CAPABILITIES))
    << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_EXTENSIONS, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, cl_ulong);
  s << "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE: "
    << device_mem_cache_type_to_string(
           device_info<cl_device_mem_cache_type>(device_id_, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE))
    << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_GLOBAL_MEM_SIZE, cl_ulong);
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
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE_SUPPORT, cl_bool);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_HEIGHT, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE2D_MAX_WIDTH, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_DEPTH, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_HEIGHT, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_IMAGE3D_MAX_WIDTH, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong);
  s << "CL_DEVICE_LOCAL_MEM_TYPE: "
    << device_local_mem_type_to_string(
           device_info<cl_device_local_mem_type>(device_id_, CL_DEVICE_LOCAL_MEM_TYPE))
    << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_ARGS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, cl_ulong);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_MEM_ALLOC_SIZE, cl_ulong);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_PARAMETER_SIZE, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_READ_IMAGE_ARGS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_SAMPLERS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_GROUP_SIZE, size_t);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, cl_uint);
  s << "CL_DEVICE_MAX_WORK_ITEM_SIZES: " << max_work_item_sizes_to_string(device_id_) << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MAX_WRITE_IMAGE_ARGS, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MEM_BASE_ADDR_ALIGN, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NAME, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PROFILE, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_PROFILING_TIMER_RESOLUTION, size_t);
  s << "CL_DEVICE_QUEUE_PROPERTIES: "
    << command_queue_properties_to_string(
           device_info<cl_command_queue_properties>(device_id_, CL_DEVICE_QUEUE_PROPERTIES))
    << "\n";
  s << "CL_DEVICE_SINGLE_FP_CONFIG: "
    << device_fp_config_to_string(
           device_info<cl_device_fp_config>(device_id_, CL_DEVICE_SINGLE_FP_CONFIG))
    << "\n";
  s << "CL_DEVICE_TYPE: "
    << device_type_to_string(device_info<cl_device_type>(device_id_, CL_DEVICE_TYPE)) << "\n";
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VENDOR, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VENDOR_ID, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_VERSION, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DRIVER_VERSION, std::string);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, cl_uint);
  SGE_OPENCL_DEVICE_OUTPUT_SINGLE_INFO(CL_DEVICE_HOST_UNIFIED_MEMORY, cl_bool);
}

bool sge::opencl::device::object::is_gpu() const
{
  cl_device_type type{};

  cl_int const error_code =
      clGetDeviceInfo(device_id_, CL_DEVICE_TYPE, sizeof(cl_device_type), &type, nullptr);

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetDeviceInfo(option value)"));

  return type == CL_DEVICE_TYPE_GPU; // NOLINT(hicpp-signed-bitwise)
}

sge::opencl::device::object::object(cl_device_id const &_device_id) : device_id_(_device_id) {}
