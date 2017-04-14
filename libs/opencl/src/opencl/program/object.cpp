/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/log/default_parameters.hpp>
#include <sge/opencl/exception.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/container/data.hpp>
#include <fcppt/container/buffer/object.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/container/raw_vector/object_impl.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>
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
	fcppt::log::context &_log_context,
	sge::opencl::context::object &_context,
	sge::opencl::program::source_string_sequence const &_source_strings,
	sge::opencl::program::optional_build_parameters const &_opt_params)
:
	object(
		_log_context
	)
{
	typedef
	std::vector<char const *>
	string_ptr_vector;

	typedef
	std::vector<size_t>
	length_vector;

	string_ptr_vector strings;

	strings.reserve(
		static_cast<string_ptr_vector::size_type>(
			_source_strings.size()));

	length_vector lengths;

	lengths.reserve(
		static_cast<length_vector::size_type>(
			_source_strings.size()));

	// TODO: map
	for(
		program::source_string_sequence::const_iterator source_string =
			_source_strings.begin();
		source_string != _source_strings.end();
		++source_string)
	{
		strings.push_back(
			source_string->c_str());
		lengths.push_back(
			static_cast<size_t>(
				source_string->length()));
	}

	cl_int error_code;

	program_ =
		clCreateProgramWithSource(
			_context.context_,
			static_cast<cl_uint>(
				_source_strings.size()),
			strings.data(),
			lengths.data(),
			&error_code);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateProgramWithSource"));

	FCPPT_ASSERT_POST(
		program_,
		sge::opencl::exception);

	fcppt::optional::maybe_void(
		_opt_params,
		[
			this
		](
			sge::opencl::program::build_parameters const &_params
		)
		{
			this->build(
				_params
			);
		}
	);
}

cl_program
sge::opencl::program::object::impl() const
{
	return program_;
}

void
sge::opencl::program::object::build(
	program::build_parameters const &params)
{
	device_id_vector const devices(
		fcppt::optional::maybe(
			params.devices(),
			[
				this
			]{
				return
					this->program_devices();
			},
			[](
				sge::opencl::device::object_ref_sequence const &_devices
			)
			{
				return
					fcppt::algorithm::map<
						device_id_vector
					>(
						_devices,
						[](
							fcppt::reference<
								sge::opencl::device::object
							> const _device
						)
						{
							return
								_device.get().device_id_;
						}
					);
			}
		)
	);

	notification_callback_ =
		params.notification_callback();

	//cl_int const error_code3 =
		clBuildProgram(
			program_,
			static_cast<cl_uint>(
					devices.size()),
			devices.data(),
			params.build_options().empty()
			?
				nullptr
			:
				params.build_options().c_str(),
			params.notification_callback().has_value()
			?
				&object::notification_callback
			:
				nullptr,
			params.notification_callback().has_value()
			?
				this
			:
				nullptr
		);

	// One of the rare cases where we explicitly handle the error
//	if(error_code3 == CL_SUCCESS)
//		return;

	this->check_program_return_values();
}

sge::opencl::program::object::~object()
{
	if(!program_)
		return;

	cl_int const error_code =
		clReleaseProgram(
			program_);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseProgram"));
}

sge::opencl::program::object::object(
	fcppt::log::context &_log_context
)
:
	log_{
		_log_context,
		sge::opencl::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("program::object")
			}
		)
	},
	// TODO: Direct initialization
	program_(nullptr),
	notification_callback_()
{
}

sge::opencl::program::object::device_id_vector
sge::opencl::program::object::program_devices() const
{
	// We need the device vector anyway when we handle the
	// errors, so we get it here. Hope it's not too much
	// of a performance penalty.
	cl_uint number_of_devices;

	cl_int const error_code =
		clGetProgramInfo(
			program_,
			CL_PROGRAM_NUM_DEVICES,
			sizeof(cl_uint),
			&number_of_devices,
			nullptr);

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_NUM_DEVICES)"));

	fcppt::container::buffer::object<
		cl_device_id
	> devices{
		fcppt::cast::size<
			device_id_vector::size_type
		>(
			number_of_devices
		)
	};

	cl_int const error_code2 =
		clGetProgramInfo(
			program_,
			CL_PROGRAM_DEVICES,
			static_cast<size_t>(
				sizeof(cl_device_id) * devices.write_size()),
			devices.write_data(),
			nullptr);

	devices.written(
		devices.write_size()
	);

	sge::opencl::impl::handle_error(
		error_code2,
		FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_DEVICES)"));

	return
		fcppt::container::buffer::to_raw_vector(
			std::move(
				devices
			)
		);
}

void
sge::opencl::program::object::check_program_return_values()
{
	device_id_vector const devices =
		this->program_devices();

	// TODO: Normal loop
	for(
		device_id_vector::const_iterator it =
			devices.begin();
		it != devices.end();
		++it)
	{
		cl_build_status return_status;

		cl_int const error_code4 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_STATUS,
				sizeof(
					cl_build_status),
				&return_status,
				nullptr);

		opencl::impl::handle_error(
			error_code4,
			FCPPT_TEXT("clGetProgramBuildInfo(Build status of a device)"));

		FCPPT_ASSERT_ERROR(
			return_status != CL_BUILD_NONE);

		// This will only be sent if we specify a callback
		FCPPT_ASSERT_ERROR(
			notification_callback_.has_value() ||
			return_status != CL_BUILD_IN_PROGRESS);

		if(return_status == CL_BUILD_SUCCESS)
			continue;

		std::size_t program_build_log_size;
		cl_int const error_code5 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_LOG,
				0,
				nullptr,
				&program_build_log_size);

		opencl::impl::handle_error(
			error_code5,
			FCPPT_TEXT("clGetProgramBuildInfo(Build log size)"));

		std::string build_log;
		build_log.resize(
			static_cast<std::string::size_type>(
				program_build_log_size));

		cl_int const error_code6 =
			clGetProgramBuildInfo(
				program_,
				*it,
				CL_PROGRAM_BUILD_LOG,
				program_build_log_size,
				fcppt::container::data(
					build_log
				),
				nullptr);

		opencl::impl::handle_error(
			error_code6,
			FCPPT_TEXT("clGetProgramBuildInfo(Build log string)"));

		if(!build_log.empty())
		{
			// TODO: error?
			FCPPT_LOG_VERBOSE(
				log_,
				fcppt::log::_
					<< FCPPT_TEXT("Program build failed, build log:\n")
					<< fcppt::from_std_string(build_log));
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

void
sge::opencl::program::object::notification_callback(
	cl_program,
	void *user_data)
{
	sge::opencl::program::object * const program =
		static_cast<sge::opencl::program::object *>(
			user_data);

	program->check_program_return_values();

	FCPPT_ASSERT_OPTIONAL_ERROR(
		program->notification_callback_
	)();
}
