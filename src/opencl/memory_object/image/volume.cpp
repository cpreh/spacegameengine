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
#include <sge/opencl/memory_object/image/volume.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <sge/src/opencl/memory_object/to_opencl_mem_flags.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::opencl::memory_object::image::volume::volume(
	context::object &_context,
	memory_object::flags_field const &_mem_flags,
	renderer::texture::volume &_renderer_texture)
:
	impl_(),
	image_format_(),
	size_(
		fcppt::math::dim::structure_cast<memory_object::dim3>(
			_renderer_texture.area().size()))
{
	cl_int error_code;
	impl_ =
		clCreateFromGLTexture3D(
			_context.impl(),
			memory_object::to_opencl_mem_flags(
				_mem_flags),
			dynamic_cast<renderer::opengl::texture::base &>(
				_renderer_texture).type().get(),
			// mip level
			0,
			dynamic_cast<renderer::opengl::texture::base &>(
				_renderer_texture).id().get(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateFromGLTexture3D()"));

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
sge::opencl::memory_object::image::volume::impl()
{
	return impl_;
}

cl_image_format const &
sge::opencl::memory_object::image::volume::image_format() const
{
	return image_format_;
}

sge::opencl::memory_object::dim3 const &
sge::opencl::memory_object::image::volume::size() const
{
	return size_;
}

sge::opencl::memory_object::image::volume::~volume()
{
	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(volume texture)"));
}
