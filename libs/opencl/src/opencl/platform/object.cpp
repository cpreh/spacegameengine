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


#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/platform/profile_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{
std::string
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
			nullptr, // param value (we don't want that, yet)
			&param_value_size);

	sge::opencl::impl::handle_error(
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
			nullptr);

	sge::opencl::impl::handle_error(
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

sge::opencl::platform::profile_type
sge::opencl::platform::object::profile() const
{
	return
		platform_info_string(
			platform_id_,
			CL_PLATFORM_PROFILE) == "FULL_PROFILE"
		?
			sge::opencl::platform::profile_type::full
		:
			sge::opencl::platform::profile_type::embedded;
}

sge::opencl::platform::version
sge::opencl::platform::object::version() const
{
	return
		sge::opencl::platform::version(
			platform_info_string(
				platform_id_,
				CL_PLATFORM_VERSION));
}

std::string
sge::opencl::platform::object::name() const
{
	return
		platform_info_string(
			platform_id_,
			CL_PLATFORM_NAME);
}

sge::opencl::platform::extension_sequence
sge::opencl::platform::object::extensions() const
{
	sge::opencl::platform::extension_sequence result;

	std::string const info_string(
		platform_info_string(
			platform_id_,
			CL_PLATFORM_EXTENSIONS));

	boost::algorithm::split(
		result,
		info_string,
		boost::algorithm::is_any_of(
			" "));
	return result;
}

bool
sge::opencl::platform::object::supports_memory_sharing_with(
	renderer::device::core const &) const
{
	return
		fcppt::algorithm::contains(
			this->extensions(),
			"cl_khr_gl_sharing");
}

bool
sge::opencl::platform::object::has_gpu() const
{
	for(
		auto const &device : devices_
	)
		if (device.is_gpu())
			return true;

	return false;
}

std::string
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
			nullptr,
			&number_of_devices);

	opencl::impl::handle_error(
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
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceIDs"));

	for(
		auto const &id : device_ids
	)
		devices_.push_back(
			sge::opencl::device::object(
				id));
}

sge::opencl::platform::object::object(
	object &&
) = default;

sge::opencl::platform::object &
sge::opencl::platform::object::operator=(
	object &&
) = default;

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
