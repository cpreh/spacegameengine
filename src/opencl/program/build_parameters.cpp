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


#include <sge/opencl/program/build_parameters.hpp>

sge::opencl::program::build_parameters::build_parameters()
:
	devices_(),
	build_options_(),
	notification_callback_()
{
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::devices(
	device::object_ref_sequence const &_devices)
{
	devices_ =
		_devices;
	return *this;
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::options(
	program::build_options const &_build_options)
{
	build_options_ =
		_build_options;
	return *this;
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::notification_callback(
	program::notification_callback const &_notification_callback)
{
	notification_callback_ =
		_notification_callback;
	return *this;
}

fcppt::optional<sge::opencl::device::object_ref_sequence> const &
sge::opencl::program::build_parameters::devices() const
{
	return devices_;
}

sge::opencl::program::build_options const &
sge::opencl::program::build_parameters::build_options() const
{
	return build_options_;
}

sge::opencl::program::notification_callback const &
sge::opencl::program::build_parameters::notification_callback() const
{
	return notification_callback_;
}
