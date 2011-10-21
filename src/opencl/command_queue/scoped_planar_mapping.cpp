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


#include "../handle_error.hpp"
#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::opencl::command_queue::scoped_planar_mapping::scoped_planar_mapping(
	command_queue::object &_queue,
	opencl::memory_object::image::planar &_image,
	cl_map_flags const _flags,
	opencl::memory_object::rect const &_rect)
:
	queue_(
		_queue),
	rect_(
		_rect),
	sge_image_format_(
		opencl::memory_object::image::opencl_color_format_to_sge(
			_image.image_format())),
	image_(
		_image.impl()),
	ptr_(
		0),
	pitch_()
{
	cl_int error_code;

	// We can't use _rect.pos().data() because OpenCL checks if [2] is equal to 0/1
	std::size_t pos[] = { _rect.pos()[0],_rect.pos()[1],0 };
	std::size_t size[] = { _rect.size()[0],_rect.size()[1],1 };

	ptr_ =
		clEnqueueMapImage(
			_queue.impl(),
			image_,
			// Blocking: yes
			CL_TRUE,
			_flags,
			pos,
			size,
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

sge::image2d::view::object const
sge::opencl::command_queue::scoped_planar_mapping::view()
{
	return
		sge::image2d::view::make(
			static_cast<sge::image::raw_pointer>(
				ptr_),
			fcppt::math::dim::structure_cast<sge::image2d::dim>(
				rect_.size()),
			sge_image_format_,
			image2d::pitch(
				static_cast<image2d::pitch::value_type>(
					pitch_ -
					rect_.w() *
					sge::image::color::format_stride(
						sge_image_format_))));
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
