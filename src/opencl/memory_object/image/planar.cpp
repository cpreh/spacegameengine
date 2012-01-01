/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opencl/context/object.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <sge/src/opencl/memory_object/to_opencl_mem_flags.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::opencl::memory_object::image::planar::planar(
	context::object &_context,
	memory_object::flags_field const &_mem_flags,
	cl_image_format const &_image_format,
	memory_object::dim2 const &_size,
	image::planar_pitch const &_pitch)
:
	impl_(),
	image_format_(
		_image_format),
	size_(
		_size)
{
	FCPPT_ASSERT_PRE(
		_image_format.image_channel_order != CL_RGB ||
		(
			_image_format.image_channel_data_type != CL_UNORM_SHORT_565 &&
			_image_format.image_channel_data_type != CL_UNORM_SHORT_555
			// Nvidia doesn't define this constant
			/* && _image_format.image_channel_data_type != CL_UNORM_INT101010*/));

	FCPPT_ASSERT_PRE(
		_image_format.image_channel_order != CL_INTENSITY ||
		(
			_image_format.image_channel_data_type == CL_UNORM_INT8 ||
			_image_format.image_channel_data_type == CL_UNORM_INT16 ||
			_image_format.image_channel_data_type == CL_SNORM_INT8 ||
			_image_format.image_channel_data_type == CL_SNORM_INT16 ||
			_image_format.image_channel_data_type == CL_HALF_FLOAT ||
			_image_format.image_channel_data_type == CL_FLOAT));

	FCPPT_ASSERT_PRE(
		_image_format.image_channel_order != CL_LUMINANCE ||
		(
			_image_format.image_channel_data_type == CL_UNORM_INT8 ||
			_image_format.image_channel_data_type == CL_UNORM_INT16 ||
			_image_format.image_channel_data_type == CL_SNORM_INT8 ||
			_image_format.image_channel_data_type == CL_SNORM_INT16 ||
			_image_format.image_channel_data_type == CL_HALF_FLOAT ||
			_image_format.image_channel_data_type == CL_FLOAT));

	FCPPT_ASSERT_PRE(
		(_image_format.image_channel_order != CL_ARGB && _image_format.image_channel_order != CL_BGRA) ||
		(
			_image_format.image_channel_data_type == CL_UNORM_INT8 ||
			_image_format.image_channel_data_type == CL_SNORM_INT8 ||
			_image_format.image_channel_data_type == CL_SIGNED_INT8 ||
			_image_format.image_channel_data_type == CL_UNSIGNED_INT8));


	cl_int error_code;

#ifndef CL_USE_DEPRECATED_OPENCL_1_1_APIS
	cl_image_desc image_description;
	image_description.image_width = _size.w();
	image_description.image_height = _size.h();
	image_description.image_row_pitch = _pitch.get();
	image_description.num_mip_levels = 0;
	image_description.num_samples = 0;

	impl_ =
		clCreateImage(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_mem_flags),
			&_image_format,
			&image_description,
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateImage(planar texture)"));
#else
	impl_ =
		clCreateImage2D(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_mem_flags),
			&_image_format,
			_size.w(),
			_size.h(),
			_pitch.get(),
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateImage(planar texture)"));
#endif
}

sge::opencl::memory_object::image::planar::planar(
	context::object &_context,
	memory_object::flags_field const &_mem_flags,
	renderer::texture::planar &_renderer_texture)
:
	impl_(),
	image_format_(),
	size_(
		fcppt::math::dim::structure_cast<memory_object::dim2>(
			_renderer_texture.area().size()))
{
	cl_int error_code;
	impl_ =
		clCreateFromGLTexture2D(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_mem_flags),
			GL_TEXTURE_2D,
			// mip level
			0,
			dynamic_cast<renderer::opengl::texture::base &>(
				_renderer_texture).id().get(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateFromGLTexture2D()"));

	error_code =
		clGetImageInfo(
			impl_,
			CL_IMAGE_FORMAT,
			sizeof(cl_image_format),
			&image_format_,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetImageInfo(image format)"));
}


cl_mem
sge::opencl::memory_object::image::planar::impl()
{
	return impl_;
}

cl_image_format const &
sge::opencl::memory_object::image::planar::image_format() const
{
	return image_format_;
}

sge::opencl::memory_object::dim2 const &
sge::opencl::memory_object::image::planar::size() const
{
	return size_;
}

sge::opencl::memory_object::image::planar::~planar()
{
	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(planar texture)"));
}
