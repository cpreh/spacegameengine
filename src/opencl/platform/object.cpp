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
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/clinclude.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{
std::string const
platform_info_string(
	cl_platform_id const &p,
	cl_platform_info const &info)
{
	size_t param_value_size;

	cl_int error_code =
		clGetPlatformInfo(
			p,
			info,
			0, // param value size (we don't know that, yet)
			0, // param value (we don't want that, yet)
			&param_value_size);

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetPlatformInfo"));

	fcppt::container::raw_vector<char> result_string(
		static_cast<fcppt::container::raw_vector<char>::size_type>(
			param_value_size));

  error_code =
		clGetPlatformInfo(
			p,
			info,
			param_value_size,
			result_string.data(),
			// param value size
			0);

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetPlatformInfo"));

	return
		std::string(
			result_string.data());
}
}

cl_platform_id
sge::opencl::platform::object::impl() const
{
	return platform_id_;
}

sge::opencl::device::object_sequence &
sge::opencl::platform::object::devices()
{
	return devices_;
}

sge::opencl::device::object_sequence const &
sge::opencl::platform::object::devices() const
{
	return devices_;
}

sge::opencl::profile_type::type
sge::opencl::platform::object::profile() const
{
	return
		platform_info_string(
			platform_id_,
			CL_PLATFORM_PROFILE) == "FULL_PROFILE"
		?
			opencl::profile_type::full
		:
			opencl::profile_type::embedded;
}

sge::opencl::version const
sge::opencl::platform::object::version() const
{
	return
		opencl::version(
			platform_info_string(
				platform_id_,
				CL_PLATFORM_VERSION));
}

std::string const
sge::opencl::platform::object::name() const
{
	return
		platform_info_string(
			platform_id_,
			CL_PLATFORM_NAME);
}

sge::opencl::extension_sequence const
sge::opencl::platform::object::extensions() const
{
	sge::opencl::extension_sequence result;
	boost::algorithm::split(
		result,
		platform_info_string(
			platform_id_,
			CL_PLATFORM_EXTENSIONS),
		boost::algorithm::is_any_of(
			" "));
	return result;
}

bool
sge::opencl::platform::object::supports_memory_sharing_with(
	renderer::device const &) const
{
	return
		fcppt::algorithm::contains(
			this->extensions(),
			"cl_khr_gl_sharing");
}

std::string const
sge::opencl::platform::object::vendor() const
{
	return
		platform_info_string(
			platform_id_,
			CL_PLATFORM_VENDOR);
}

sge::opencl::platform::object::~object()
{
}

sge::opencl::platform::object::object(
	cl_platform_id const &_platform_id)
:
	platform_id_(
		_platform_id),
	devices_()
{
	cl_uint number_of_devices;

	cl_int error_code =
		clGetDeviceIDs(
			platform_id_,
			CL_DEVICE_TYPE_ALL,
			// Number of entries
			0,
			// Device data
			0,
			&number_of_devices);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceIDs"));

	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_sequence;

	device_id_sequence device_ids(
		static_cast<device_id_sequence::size_type>(
			number_of_devices));

	error_code =
		clGetDeviceIDs(
			platform_id_,
			CL_DEVICE_TYPE_ALL,
			// Number of entries
			number_of_devices,
			// Device data
			device_ids.data(),
			// Pointer to the number of devices
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceIDs"));

	for(
		device_id_sequence::const_iterator device_it =
			device_ids.begin();
		device_it != device_ids.end();
		++device_it)
		devices_.push_back(
			new opencl::device::object(
				*device_it));
		/*
		fcppt::container::ptr::push_back_unique_ptr(
			devices_,
			fcppt::make_unique_ptr<opencl::device>(
				*device_it));*/
}

/*
void
sge::opencl::platform::object::error_callback(
	char const *error_info_string,
	void const *binary_data,
	size_t const size_of_binary_data,
	void *user_data)
{
	static_cast<opencl::platform *>(user_data).error_callback
}
*/
