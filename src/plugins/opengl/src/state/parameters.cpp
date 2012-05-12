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
#include <sge/opengl/state/parameters.hpp>
#include <sge/opengl/state/deferred/object_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>


sge::opengl::state::parameters::parameters(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::state::deferred::object &_deferred,
	sge::renderer::depth_stencil_buffer::type const _depth_stencil_buffer
)
:
	system_context_(
		_system_context
	),
	deferred_(
		_deferred
	),
	depth_stencil_buffer_(
		_depth_stencil_buffer
	)
{
}

sge::opengl::context::system::object &
sge::opengl::state::parameters::system_context() const
{
	return system_context_;
}

sge::opengl::state::deferred::object &
sge::opengl::state::parameters::deferred() const
{
	return deferred_;
}

sge::renderer::depth_stencil_buffer::type
sge::opengl::state::parameters::depth_stencil_buffer() const
{
	return depth_stencil_buffer_;
}
