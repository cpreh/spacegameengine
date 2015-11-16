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


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/draw_context.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/convert/primitive_type.hpp>
#include <sge/opengl/index/buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


void
sge::opengl::draw_elements(
	sge::opengl::context::object &_context,
	sge::renderer::index::buffer const &_index_buffer,
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type,
	sge::renderer::index::first const _first_index,
	sge::renderer::index::count const _num_indices
)
{
	if(
		_primitive_type
		==
		sge::renderer::primitive_type::point_list
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Rendering point lists with index buffers is not portable!")
		);
	}

	if(
		_num_vertices.get()
		==
		0u
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Empty render() call with index_buffer. ")
				<< FCPPT_TEXT("vertex_count was 0.")
		);

		return;
	}

	sge::opengl::draw_context const &context(
		sge::opengl::context::use<
			sge::opengl::draw_context
		>(
			_context,
			_context.info()
		)
	);

	sge::opengl::index::buffer const &gl_index_buffer(
		fcppt::cast::static_downcast<
			sge::opengl::index::buffer const &
		>(
			_index_buffer
		)
	);

	gl_index_buffer.bind();

	GLenum const primitive_type(
		sge::opengl::convert::primitive_type(
			_primitive_type
		)
	);

	GLsizei const element_count(
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_num_indices.get()
			)
		)
	);

	GLenum const format(
		gl_index_buffer.gl_format()
	);

	GLvoid const *const offset(
		gl_index_buffer.buffer_offset(
			_first_index
		)
	);

	fcppt::maybe(
		context.draw_range_elements(),
		[
			primitive_type,
			element_count,
			format,
			offset
		]{
			sge::opengl::call(
				::glDrawElements,
				primitive_type,
				element_count,
				format,
				offset
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glDrawElements failed"),
				sge::renderer::exception
			)
		},
		[
			primitive_type,
			element_count,
			format,
			offset,
			_first_vertex,
			_num_vertices
		](
			sge::opengl::draw_context::gl_draw_range_elements _draw_elements
		)
		{
			_draw_elements(
				primitive_type,
				fcppt::cast::size<
					GLuint
				>(
					_first_vertex.get()
				),
				fcppt::cast::size<
					GLuint
				>(
					_first_vertex.get()
					+
					_num_vertices.get()
					- 1u
				),
				element_count,
				format,
				offset
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glDrawRangeElements failed"),
				sge::renderer::exception
			)
		}
	);
}
