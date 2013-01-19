/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>


sge::opengl::texture::basic_parameters::basic_parameters(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context
)
:
	system_context_(
		_system_context
	),
	device_context_(
		_device_context
	)
{
}

sge::opengl::context::system::object &
sge::opengl::texture::basic_parameters::system_context() const
{
	return
		system_context_;
}

sge::opengl::context::device::object &
sge::opengl::texture::basic_parameters::device_context() const
{
	return
		device_context_;
}
