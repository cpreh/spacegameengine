#include "../../handle_error.hpp"
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/context/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>

sge::opencl::memory_object::image::planar::planar(
	context::object &_context,
	cl_mem_flags const _mem_flags,
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
			_pitch.get(),
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateImage2D(planar texture)"));
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
