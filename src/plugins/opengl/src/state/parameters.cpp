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


#include <sge/opengl/state/parameters.hpp>
#include <sge/opengl/state/deferred/object_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/multi_sample_context.hpp>
#include <sge/opengl/point_sprite_context.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>

sge::opengl::state::parameters::parameters(
	opengl::context::object &_context,
	state::deferred::object &_deferred,
	renderer::depth_stencil_buffer::type const _depth_stencil_buffer
)
:
	multi_sample_context_(
		opengl::context::use<
			opengl::multi_sample_context
		>(
			_context
		)
	),
	point_sprite_context_(
		context::use<
			opengl::point_sprite_context
		>(
			_context
		)
	),
	deferred_(
		_deferred
	),
	depth_stencil_buffer_(
		_depth_stencil_buffer
	)
{
}

sge::opengl::multi_sample_context &
sge::opengl::state::parameters::multi_sample_context() const
{
	return multi_sample_context_;
}

sge::opengl::point_sprite_context &
sge::opengl::state::parameters::point_sprite_context() const
{
	return point_sprite_context_;
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
