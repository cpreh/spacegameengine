/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/unset_vertex_buffer.hpp>
#include <sge/opengl/vertex_buffer.hpp>
#include <sge/opengl/vertex_context.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::opengl::unset_vertex_buffer(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::buffer const &_buffer
)
{
	sge::opengl::vertex_context &context(
		sge::opengl::context::use<
			sge::opengl::vertex_context
		>(
			_context
		)
	);

	sge::renderer::vf::dynamic::part_index const index(
		_buffer.format_part_index()
	);

	fcppt::cast::static_downcast<
		sge::opengl::vertex_buffer const &
	>(
		_buffer
	).unuse(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			context.vertex_declaration()
		).gl_format_part(
			index
		)
	);

	context.vertex_buffer(
		index,
		sge::opengl::vertex_context::optional_vertex_buffer()
	);
}
