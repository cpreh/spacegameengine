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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>


sge::opengl::vf::actor_parameters::actor_parameters(
	sge::renderer::vf::dynamic::stride const _stride,
	sge::renderer::vf::dynamic::offset const _offset,
	sge::opengl::context::system::object &_system_context
)
:
	stride_(
		_stride
	),
	offset_(
		_offset
	),
	system_context_(
		_system_context
	)
{
}

sge::renderer::vf::dynamic::stride const
sge::opengl::vf::actor_parameters::stride() const
{
	return stride_;
}

sge::renderer::vf::dynamic::offset const
sge::opengl::vf::actor_parameters::offset() const
{
	return offset_;
}

sge::opengl::context::system::object &
sge::opengl::vf::actor_parameters::system_context() const
{
	return system_context_;
}
