/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::opencl::command_queue::scoped_planar_mapping::scoped_planar_mapping(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::memory_object::image::planar &_image,
	sge::opencl::command_queue::map_flags const _flags,
	sge::opencl::memory_object::rect const &_rect,
	sge::opencl::event::sequence const &_events)
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
		nullptr),
	pitch_()
{
	cl_int error_code;

	// We can't use _rect.pos().data() because OpenCL checks if [2] is equal to 0/1
	std::size_t pos[] = { _rect.pos().x(),_rect.pos().y(),0 };
	std::size_t size[] = { _rect.size().w(),_rect.size().h(),1 };

	ptr_ =
		clEnqueueMapImage(
			_queue.impl(),
			image_,
			// Blocking: yes
			CL_TRUE,
			sge::opencl::command_queue::map_flags_to_native(
				_flags),
			pos,
			size,
			&pitch_,
			// slice pitch
			nullptr,
			static_cast<cl_uint>(
				_events.size()),
			_events.empty()
			?
				nullptr
			:
				sge::opencl::impl::event::flatten_sequence(
					_events).data(),
			// event
			nullptr,
			&error_code);

	opencl::impl::handle_error(
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

sge::image2d::view::object
sge::opencl::command_queue::scoped_planar_mapping::view()
{
	return
		sge::image2d::view::make(
			static_cast<sge::image::raw_pointer>(
				ptr_),
			fcppt::math::dim::structure_cast<
				sge::image2d::dim,
				fcppt::cast::size_fun
			>(
				rect_.size()
			),
			sge_image_format_,
			image2d::pitch(
				static_cast<image2d::pitch::value_type>(
					pitch_ -
					rect_.size().w() *
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
			nullptr,
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueUnmapMemObject"));
}
