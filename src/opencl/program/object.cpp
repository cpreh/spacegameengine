#include "../handle_error.hpp"
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/exception.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/text.hpp>

sge::opencl::program::object::object(
	context::object &_context,
	program::device_blob_map const &_blobs)
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
}

sge::opencl::program::object::object(
	context::object &_context,
	program::source_string_sequence const &_source_strings)
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
	bool const has_devices =
		params.devices();

	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_vector;

	device_id_vector devices;

	if(has_devices)
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

	cl_int const error_code =
		clBuildProgram(
			program_,
			has_devices
			?
				static_cast<cl_uint>(
					devices.size())
			:
				0,
			has_devices
			?
				devices.data()
			:
				0,
			params.build_options().c_str(),
			params.notification_callback()
			?
				&object::notification_callback
			:
				0,
			this);

	notification_callback_ =
		params.notification_callback();

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clBuildProgram"));
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
