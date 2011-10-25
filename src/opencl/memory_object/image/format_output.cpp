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


#include <sge/opencl/memory_object/image/format_output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(constant) case constant: s << #constant; break

void
sge::opencl::memory_object::image::format_output(
	std::ostream &s,
	cl_image_format const &_if)
{
	switch(_if.image_channel_order)
	{
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_R);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_A);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_INTENSITY);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_LUMINANCE);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_RG);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_RA);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_RGB);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_RGBA);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_ARGB);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_BGRA);
	}

	s << " ";

	switch(_if.image_channel_data_type)
	{
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_SNORM_INT8);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_SNORM_INT16);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNORM_INT8);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNORM_INT16);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNORM_SHORT_565);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNORM_SHORT_555);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNORM_INT_101010);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_SIGNED_INT8);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_SIGNED_INT16);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_SIGNED_INT32);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNSIGNED_INT8);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNSIGNED_INT16);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_UNSIGNED_INT32);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_HALF_FLOAT);
		SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(
			CL_FLOAT);
	}
}
