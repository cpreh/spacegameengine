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


#include <sge/opencl/single_device_system/parameters.hpp>

sge::opencl::single_device_system::parameters::parameters()
:
	renderer_(),
	error_callback_(),
	profiling_(
		command_queue::profiling_mode::disabled),
	prefers_gpu_(
		false)
{
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::renderer(
	sge::renderer::device &_renderer)
{
	renderer_ =
		opencl::optional_renderer(
			_renderer);
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::enable_profiling()
{
	profiling_ = command_queue::profiling_mode::enabled;
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::context_error_callback(
	opencl::context::error_callback const &_error_callback)
{
	error_callback_ =
		opencl::context::optional_error_callback(
			_error_callback);
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::prefer_gpu()
{
	prefers_gpu_ =
		true;
	return *this;
}

sge::opencl::optional_renderer const &
sge::opencl::single_device_system::parameters::renderer() const
{
	return
		renderer_;
}

sge::opencl::context::optional_error_callback const &
sge::opencl::single_device_system::parameters::error_callback() const
{
	return error_callback_;
}

sge::opencl::command_queue::profiling_mode::type
sge::opencl::single_device_system::parameters::profiling() const
{
	return profiling_;
}

bool
sge::opencl::single_device_system::parameters::prefers_gpu() const
{
	return prefers_gpu_;
}
