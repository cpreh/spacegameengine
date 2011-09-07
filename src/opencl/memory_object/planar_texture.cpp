#include "../handle_error.hpp"
#include <sge/opencl/memory_object/planar_texture.hpp>
#include <sge/opencl/context/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>

sge::opencl::memory_object::planar_texture::planar_texture(
	context::object &_context,
	cl_mem_flags const _mem_flags,
	cl_image_format const &_image_format,
	memory_object::dim2 const &_size,
	memory_object::dim2::value_type const _pitch)
:
	impl_(),
	image_format_(
		_image_format)
{
	FCPPT_ASSERT_PRE(
		_mem_flags != CL_MEM_USE_HOST_PTR);

	FCPPT_ASSERT_PRE(
		_mem_flags != CL_MEM_COPY_HOST_PTR);

	cl_int error_code;
	impl_ =
		clCreateImage2D(
			_context.impl(),
			_mem_flags,
  			&_image_format,
			_size.w(),
			_size.h(),
			_pitch,
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateImage2D(planar texture)"));
}

cl_mem
sge::opencl::memory_object::planar_texture::impl()
{
	return impl_;
}

cl_image_format const &
sge::opencl::memory_object::planar_texture::image_format() const
{
	return image_format_;
}

sge::opencl::memory_object::planar_texture::~planar_texture()
{
	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(planar texture)"));
}
