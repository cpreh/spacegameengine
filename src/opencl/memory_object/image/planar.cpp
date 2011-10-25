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


#include <sge/opencl/context/object.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <sge/src/opencl/memory_object/to_opencl_mem_flags.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl_gl.h>
#include <fcppt/config/external_end.hpp>


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
	cl_int error_code;
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
		FCPPT_TEXT("clCreateImage2D(planar texture)"));
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
