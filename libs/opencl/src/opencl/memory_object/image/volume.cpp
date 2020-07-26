//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/memory_object/to_opencl_mem_flags.hpp>
#include <sge/opencl/memory_object/image/volume.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::opencl::memory_object::image::volume::volume(
	sge::opencl::context::object_ref const _context,
	memory_object::flags_field const &_mem_flags,
	sge::renderer::texture::volume_ref const _renderer_texture
)
:
	impl_(),
	image_format_(),
	size_(
		fcppt::math::dim::structure_cast<
			sge::opencl::dim3,
			fcppt::cast::size_fun
		>(
			_renderer_texture.get().size()
		)
	)
{
	cl_int error_code{};
	impl_ =
		clCreateFromGLTexture3D(
			_context.get().impl(),
			sge::opencl::impl::memory_object::to_opencl_mem_flags(
				_mem_flags),
			dynamic_cast<renderer::opengl::texture::base &>(
				_renderer_texture.get()
			).type().get(),
			// mip level
			0,
			dynamic_cast<renderer::opengl::texture::base &>(
				_renderer_texture.get()
			).id().get(),
			&error_code);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateFromGLTexture3D()"));

	error_code =
		clGetImageInfo(
			impl_,
			CL_IMAGE_FORMAT,
			sizeof(cl_image_format),
			&image_format_,
			nullptr);

	opencl::impl::handle_error(
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

sge::opencl::dim3 const &
sge::opencl::memory_object::image::volume::size() const
{
	return size_;
}

sge::opencl::memory_object::image::volume::~volume()
{
	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(volume texture)"));
}
