//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/default_parameters.hpp>
#include <sge/opencl/exception.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/container/data.hpp>
#include <fcppt/container/buffer/object.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/container/raw_vector/object_impl.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::opencl::program::object::object(
    fcppt::log::context_reference const _log_context,
    sge::opencl::context::object_ref const _context,
    sge::opencl::program::source_string_sequence const &_source_strings,
    sge::opencl::program::optional_build_parameters const &_opt_params)
    : object(_log_context)
{
  using string_ptr_vector = std::vector<char const *>;

  using length_vector = std::vector<size_t>;

  string_ptr_vector strings;

  strings.reserve(static_cast<string_ptr_vector::size_type>(_source_strings.size()));

  length_vector lengths;

  lengths.reserve(static_cast<length_vector::size_type>(_source_strings.size()));

  // TODO(philipp): map
  for (auto const &source_string : _source_strings)
  {
    strings.push_back(source_string.c_str());

    lengths.push_back(static_cast<size_t>(source_string.length()));
  }

  cl_int error_code{};

  program_ = clCreateProgramWithSource(
      _context.get().context_,
      static_cast<cl_uint>(_source_strings.size()),
      strings.data(),
      lengths.data(),
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateProgramWithSource"));

  if (program_ == nullptr)
  {
    throw sge::opencl::exception{FCPPT_TEXT("CL program is null")};
  }

  fcppt::optional::maybe_void(
      _opt_params,
      [this](sge::opencl::program::build_parameters const &_params) { this->build(_params); });
}

cl_program sge::opencl::program::object::impl() const { return program_; }

void sge::opencl::program::object::build(program::build_parameters const &params)
{
  device_id_vector const devices(fcppt::optional::maybe(
      params.devices(),
      [this] { return this->program_devices(); },
      [](sge::opencl::device::object_ref_sequence const &_devices)
      {
        return fcppt::algorithm::map<device_id_vector>(
            _devices,
            [](fcppt::reference<sge::opencl::device::object> const _device)
            { return _device.get().device_id_; });
      }));

  notification_callback_ = params.notification_callback();

  //cl_int const error_code3 =
  clBuildProgram(
      program_,
      static_cast<cl_uint>(devices.size()),
      devices.data(),
      params.build_options().empty() ? nullptr : params.build_options().c_str(),
      params.notification_callback().has_value() ? &object::notification_callback : nullptr,
      params.notification_callback().has_value() ? this : nullptr);

  // One of the rare cases where we explicitly handle the error
  //	if(error_code3 == CL_SUCCESS)
  //		return;

  this->check_program_return_values();
}

sge::opencl::program::object::~object()
{
  if (program_ == nullptr)
  {
    return;
  }

  cl_int const error_code = clReleaseProgram(program_);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clReleaseProgram"));
}

sge::opencl::program::object::object(fcppt::log::context_reference const _log_context)
    : log_{_log_context, sge::opencl::log_location(), sge::log::default_parameters(fcppt::log::name{FCPPT_TEXT("program::object")})},
      // TODO(philipp): Direct initialization
      program_(nullptr),
      notification_callback_()
{
}

sge::opencl::program::object::device_id_vector sge::opencl::program::object::program_devices() const
{
  // We need the device vector anyway when we handle the
  // errors, so we get it here. Hope it's not too much
  // of a performance penalty.
  cl_uint number_of_devices{};

  cl_int const error_code = clGetProgramInfo(
      program_, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint), &number_of_devices, nullptr);

  sge::opencl::impl::handle_error(
      error_code, FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_NUM_DEVICES)"));

  fcppt::container::buffer::object<cl_device_id> devices{
      fcppt::cast::size<device_id_vector::size_type>(number_of_devices)};

  cl_int const error_code2 = clGetProgramInfo(
      program_,
      CL_PROGRAM_DEVICES,
      static_cast<size_t>(sizeof(cl_device_id) * devices.write_size()),
      devices.write_data(),
      nullptr);

  devices.written(devices.write_size());

  sge::opencl::impl::handle_error(error_code2, FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_DEVICES)"));

  return fcppt::container::buffer::to_raw_vector(std::move(devices));
}

void sge::opencl::program::object::check_program_return_values()
{
  device_id_vector const devices = this->program_devices();

  for (auto const &device : devices)
  {
    cl_build_status return_status{};

    cl_int const error_code4 = clGetProgramBuildInfo(
        program_,
        device,
        CL_PROGRAM_BUILD_STATUS,
        sizeof(cl_build_status),
        &return_status,
        nullptr);

    sge::opencl::impl::handle_error(
        error_code4, FCPPT_TEXT("clGetProgramBuildInfo(Build status of a device)"));

    if (return_status == CL_BUILD_NONE)
    {
      throw sge::opencl::exception{FCPPT_TEXT("Program build returned none.")};
    }

    // This will only be sent if we specify a callback
    if (fcppt::not_(notification_callback_.has_value() || return_status != CL_BUILD_IN_PROGRESS))
    {
      throw sge::opencl::exception{
          FCPPT_TEXT("Callback specified but program build not in progress.")};
    }

    if (return_status == CL_BUILD_SUCCESS)
    {
      continue;
    }

    std::size_t program_build_log_size{};
    cl_int const error_code5 = clGetProgramBuildInfo(
        program_, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &program_build_log_size);

    opencl::impl::handle_error(error_code5, FCPPT_TEXT("clGetProgramBuildInfo(Build log size)"));

    std::string build_log;
    build_log.resize(static_cast<std::string::size_type>(program_build_log_size));

    cl_int const error_code6 = clGetProgramBuildInfo(
        program_,
        device,
        CL_PROGRAM_BUILD_LOG,
        program_build_log_size,
        fcppt::container::data(build_log),
        nullptr);

    opencl::impl::handle_error(error_code6, FCPPT_TEXT("clGetProgramBuildInfo(Build log string)"));

    if (!build_log.empty())
    {
      // TODO(philipp): error?
      FCPPT_LOG_VERBOSE(
          log_,
          fcppt::log::out << FCPPT_TEXT("Program build failed, build log:\n")
                          << fcppt::from_std_string(build_log))
    }

    /*
		if(error_code3 != CL_SUCCESS)
			throw
				program::build_error(
					fcppt::from_std_string(
						build_log));
		*/
  }
}

void sge::opencl::program::object::notification_callback(cl_program, void *user_data)
{
  auto *const program = static_cast<sge::opencl::program::object *>(user_data);

  program->check_program_return_values();

  fcppt::optional::maybe_void(
    program->notification_callback_,
    [](sge::opencl::program::notification_callback const &_callback)
    {
      _callback();
    });
}
