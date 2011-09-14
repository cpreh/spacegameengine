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
#include "../declare_local_logger.hpp"
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/exception.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/text.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/assert/error.hpp>

SGE_OPENCL_DECLARE_LOCAL_LOGGER("program::object")

sge::opencl::program::object::object(
	context::object &_context,
	program::device_blob_map const &_blobs,
	program::optional_build_parameters const &_params)
:
	program_(0)
{
	typedef
	fcppt::container::raw_vector<unsigned char const *>
	blob_ptr_vector;

	typedef
	fcppt::container::raw_vector<size_t>
	length_vector;

	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_vector;

	blob_ptr_vector blobs;

	blobs.reserve(
		static_cast<blob_ptr_vector::size_type>(
			_blobs.size()));

	length_vector lengths;

	lengths.reserve(
		static_cast<length_vector::size_type>(
			_blobs.size()));

	device_id_vector devices;

	devices.reserve(
		static_cast<device_id_vector::size_type>(
			_blobs.size()));

	for(
		program::device_blob_map::const_iterator current_blob =
			_blobs.begin();
		current_blob != _blobs.end();
		++current_blob)
	{
		blobs.push_back(
			&(*current_blob->second.begin()));
		lengths.push_back(
			static_cast<size_t>(
				current_blob->second.size()));
		devices.push_back(
			current_blob->first->device_id_);
	}

	typedef
	fcppt::container::raw_vector<cl_int>
	return_status_vector;

	// statuuus, with a long 'u' ;)
	return_status_vector return_status(
		static_cast<return_status_vector::size_type>(
			_blobs.size()));

	cl_int error_code;
	program_ =
		clCreateProgramWithBinary(
			_context.context_,
			static_cast<cl_uint>(
				_blobs.size()),
			devices.data(),
			lengths.data(),
			blobs.data(),
			return_status.data(),
			&error_code);

	for(
		return_status_vector::const_iterator current_return_status =
			return_status.begin();
		current_return_status != return_status.end();
		++current_return_status)
		opencl::handle_error(
			*current_return_status,
			FCPPT_TEXT("clCreateProgramWithBinary"));

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateProgramWithBinary"));

	if(_params)
		this->build(
			*_params);
}

sge::opencl::program::object::object(
	context::object &_context,
	program::source_string_sequence const &_source_strings,
	program::optional_build_parameters const &_params)
:
	program_(0)
{
	typedef
	fcppt::container::raw_vector<char const *>
	string_ptr_vector;

	typedef
	fcppt::container::raw_vector<size_t>
	length_vector;

	string_ptr_vector strings;

	strings.reserve(
		static_cast<string_ptr_vector::size_type>(
			_source_strings.size()));

	length_vector lengths;

	lengths.reserve(
		static_cast<length_vector::size_type>(
			_source_strings.size()));

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

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateProgramWithSource"));

	FCPPT_ASSERT_POST(
		program_,
		sge::exception);

	if(_params)
		this->build(
			*_params);
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
	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_vector;

	device_id_vector devices;

	if(params.devices())
	{
		devices.reserve(
			static_cast<device_id_vector::size_type>(
				params.devices()->size()));

		for(
			device::object_ref_sequence::const_iterator current_device =
				params.devices()->begin();
			current_device != params.devices()->end();
			++current_device)
			devices.push_back(
				(*current_device)->device_id_);
	}
	else
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
				0);

		opencl::handle_error(
			error_code,
			FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_NUM_DEVICES)"));

		devices.resize(
			static_cast<device_id_vector::size_type>(
				number_of_devices));

		cl_int const error_code2 =
			clGetProgramInfo(
				program_,
				CL_PROGRAM_DEVICES,
				static_cast<size_t>(
					sizeof(cl_device_id) * devices.size()),
				devices.data(),
				0);

		opencl::handle_error(
			error_code2,
			FCPPT_TEXT("clGetProgramInfo(CL_PROGRAM_DEVICES)"));
	}

	cl_int const error_code3 =
		clBuildProgram(
			program_,
			static_cast<cl_uint>(
					devices.size()),
			devices.data(),
			params.build_options().empty()
			?
				0
			:
				params.build_options().c_str(),
			params.notification_callback()
			?
				&object::notification_callback
			:
				0,
			params.notification_callback()
			?
				this
			:
				0);

	notification_callback_ =
		params.notification_callback();

	// One of the rare cases where we explicitly handle the error
//	if(error_code3 == CL_SUCCESS)
//		return;

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
				0);

		opencl::handle_error(
			error_code4,
			FCPPT_TEXT("clGetProgramBuildInfo(Build status of a device)"));

		FCPPT_ASSERT_ERROR(
			return_status != CL_BUILD_NONE);

		// This will only be sent if we specify a callback
		FCPPT_ASSERT_ERROR(
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
				0,
				&program_build_log_size);

		opencl::handle_error(
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
				&build_log[0],
				0);

		opencl::handle_error(
			error_code6,
			FCPPT_TEXT("clGetProgramBuildInfo(Build log string)"));

		if(!build_log.empty())
		{
			FCPPT_LOG_WARNING(
				local_log,
				fcppt::log::_ << FCPPT_TEXT("Build log:\n") << fcppt::from_std_string(build_log));
		}

		if(error_code3 != CL_SUCCESS)
			throw
				sge::exception(
					FCPPT_TEXT("Building the program failed. The build log was:\n")+
					fcppt::from_std_string(
						build_log));
	}
}

sge::opencl::program::device_blob_map const
sge::opencl::program::object::binaries() const
{
	// Problem with this function: We have to
	// - Query for the number of devices
	// - Query the devices themselves
	// - Resolve the device_ids to the sgeopencl device objects
	// The last step is the problem. The devices associated with a
	// program is a subset of all devices belonging to
	// the context. We'd have to query all these devices (and the
	// context). But I'm too lazy for that right now
	throw sge::exception(FCPPT_TEXT("Not supported right now"));

#if 0
	sge::opencl::program::device_blob_map result;

	cl_uint number_of_devices;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_NUM_DEVICES,
		sizeof(cl_uint),
		&number_of_devices,
		0);

	fcppt::container::raw_vector<cl_device_id> devices;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_DEVICES,
		static_cast<size_t>(
			sizeof(cl_device_id) * devices.size()),
		devices.data(),
		0);

	fcppt::container::raw_vector<size_t> sizes;

	clGetProgramInfo(
		program_,
		CL_PROGRAM_BINARY_SIZES,
		static_cast<size_t>(
			sizeof(size_t) * sizes.size()),
		sizes.data(),
		0);

	program::device_blob_map device_to_blob(
		static_cast<program::device_blob_map::size_type>(
			number_of_devices));

	for(program::device_blob_map::size_type i = 0; i < device_to_blob.size(); ++i)
		device_to_blob[i].first = devices[i];

	return result;
#endif
}

sge::opencl::program::object::~object()
{
	if(!program_)
		return;

	cl_int const error_code =
		clReleaseProgram(
			program_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseProgram"));
}

void
sge::opencl::program::object::notification_callback(
	cl_program,
	void *user_data)
{
	static_cast<object *>(user_data)->notification_callback_();
}
