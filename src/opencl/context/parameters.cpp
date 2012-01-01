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


#include <sge/opencl/context/parameters.hpp>


sge::opencl::context::parameters::parameters(
	platform::object &_platform,
	device::object_ref_sequence const &_device_refs)
:
	platform_(
		_platform),
	device_refs_(
		_device_refs),
	error_callback_(),
	shared_renderer_(0)
{
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::error_callback(
	opencl::context::error_callback const &_error_callback)
{
	error_callback_ =
		_error_callback;
	return *this;
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::share_with(
	renderer::device &_shared_renderer)
{
	shared_renderer_ =
		&_shared_renderer;
	return *this;
}

sge::opencl::device::object_ref_sequence const &
sge::opencl::context::parameters::device_refs() const
{
	return device_refs_;
}

sge::opencl::context::error_callback const &
sge::opencl::context::parameters::error_callback() const
{
	return error_callback_;
}

sge::renderer::device *
sge::opencl::context::parameters::shared_renderer() const
{
	return shared_renderer_;
}

sge::opencl::platform::object &
sge::opencl::context::parameters::platform() const
{
	return platform_;
}
