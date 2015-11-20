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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vertex/set_buffer.hpp>
#include <sge/opengl/vertex/unset_buffer.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::opengl::vertex::set_buffer(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::buffer const &_buffer
)
{
	sge::opengl::vertex::context &context(
		sge::opengl::context::use<
			sge::opengl::vertex::context
		>(
			_context
		)
	);

	sge::renderer::vf::dynamic::part_index const index(
		_buffer.format_part_index()
	);

	fcppt::maybe_void(
		context.vertex_buffer(
			index
		),
		[
			&_context
		](
			sge::opengl::vertex::buffer const &_old_buffer
		)
		{
			sge::opengl::vertex::unset_buffer(
				_context,
				_old_buffer
			);
		}
	);

	sge::opengl::vertex::buffer const &gl_buffer(
		fcppt::cast::static_downcast<
			sge::opengl::vertex::buffer const &
		>(
			_buffer
		)
	);

	context.vertex_buffer(
		index,
		sge::opengl::vertex::context::optional_buffer(
			gl_buffer
		)
	);

	gl_buffer.use(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			context.vertex_declaration()
		).gl_format_part(
			index
		)
	);
}
