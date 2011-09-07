#include "../handle_error.hpp"
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/memory_object/planar_texture.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/box/basic_impl.hpp>

sge::opencl::command_queue::scoped_planar_mapping::scoped_planar_mapping(
	command_queue::object &_queue,
	opencl::memory_object::planar_texture &_image,
	cl_map_flags const _flags,
	opencl::memory_object::rect const &_rect)
:
	queue_(
		_queue),
	image_(
		_image.impl()),
	ptr_(
		0),
	pitch_()
{
	cl_int error_code;

	ptr_ =
		clEnqueueMapImage(
			_queue.impl(),
			image_,
			// Blocking: yes
			CL_TRUE,
			_flags,
			_rect.pos().data(),
			_rect.size().data(),
			&pitch_,
			// slice pitch
			0,
			// event
			0,
			// event
			0,
			// event
			0,
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueMapImage"));
}

void*
sge::opencl::command_queue::scoped_planar_mapping::ptr() const
{
	return ptr_;
}

std::size_t
sge::opencl::command_queue::scoped_planar_mapping::pitch() const
{
	return pitch_;
}

sge::opencl::command_queue::scoped_planar_mapping::~scoped_planar_mapping()
{
	if(!ptr_)
		return;

	cl_int const error_code =
		clEnqueueUnmapMemObject(
			queue_.impl(),
			image_,
			this->ptr(),
			0,
			0,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueUnmapMemObject"));
}
