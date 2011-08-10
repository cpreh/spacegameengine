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


#include "../draw_elements.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include "../draw_context.hpp"
#include "../index_buffer.hpp"
#include "../context/use.hpp"
#include "../convert/indexed_primitive.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::draw_elements(
	opengl::context::object &_context,
	renderer::index_buffer const &_ib,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _ptype,
	renderer::primitive_count const _pcount,
	renderer::first_index const _first_index
)
{
	if(
		_num_vertices.get() == 0u
	)
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Empty device::render() call with index_buffer. ")
				<< FCPPT_TEXT("vertex_count was 0.")
		);

		return;
	}

	opengl::draw_context const &context(
		opengl::context::use<
			opengl::draw_context
		>(
			_context
		)
	);

	opengl::index_buffer const & gl_ib(
		dynamic_cast<
			opengl::index_buffer const &
		>(
			_ib
		)
	);

	gl_ib.bind();

	GLenum const primitive_type(
		convert::indexed_primitive(
			_ptype
		)
	);

	GLsizei const primitive_count(
		static_cast<
			GLsizei
		>(
			renderer::indices_per_primitive(
				_ptype
			)
			* _pcount.get()
		)
	);

	GLenum const format(
		gl_ib.gl_format()
	);

	GLvoid *const offset(
		gl_ib.buffer_offset(
			_first_index.get()
		)
	);

	if(
		context.draw_range_elements_supported()
	)
	{
		context.draw_range_elements()(
			primitive_type,
			static_cast<
				GLuint
			>(
				_first_vertex.get()
			),
			static_cast<
				GLuint
			>(
				_first_vertex.get()
				+
				_num_vertices.get()
				- 1u
			),
			primitive_count,
			format,
			offset
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glDrawRangeElements failed"),
			sge::renderer::exception
		)

		return;
	}

	::glDrawElements(
		primitive_type,
		primitive_count,
		format,
		offset
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDrawElements failed"),
		sge::renderer::exception
	)
}
