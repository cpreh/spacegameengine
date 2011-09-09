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


#include "handle_error.hpp"
#include <sge/opencl/system.hpp>
#include <sge/opencl/platform/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

sge::opencl::system::system()
:
	platforms_()
{
	cl_uint number_of_platforms;

  // First, query the total number of platforms
	cl_int error_code =
		clGetPlatformIDs(
			// maximum number of entries
			0,
			// pointer to the entries array
			0,
			&number_of_platforms);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetplatformIDs"));

	if(!number_of_platforms)
		return;

	typedef
	fcppt::container::raw_vector<cl_platform_id>
	platform_id_sequence;

	platform_id_sequence platform_ids(
		static_cast<platform_id_sequence::size_type>(
			number_of_platforms));

  // First, query the total number of platforms
  error_code =
		clGetPlatformIDs(
			number_of_platforms,
			platform_ids.data(),
			// pointer to the number of platforms
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetplatformIDs"));

	for(
		platform_id_sequence::const_iterator platform_it =
			platform_ids.begin();
		platform_it != platform_ids.end();
		++platform_it)
	{
		platforms_.push_back(
			new opencl::platform::object(
				*platform_it));
		/* Doesn't work, platform's constructor is private
		fcppt::container::ptr::push_back_unique_ptr(
			platforms_,
			fcppt::make_unique_ptr<opencl::platform>(
				*platform_it));
		*/
	}
}

sge::opencl::platform::object_sequence &
sge::opencl::system::platforms()
{
	return platforms_;
}

sge::opencl::platform::object_sequence const &
sge::opencl::system::platforms() const
{
	return platforms_;
}

sge::opencl::system::~system()
{
}
