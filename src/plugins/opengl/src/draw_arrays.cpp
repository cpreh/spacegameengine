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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/logger.hpp>
#include <sge/opengl/convert/primitive_type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


void
sge::opengl::draw_arrays(
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type
)
{
	if(
		_num_vertices.get() == 0u
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Empty render() call. ")
				<< FCPPT_TEXT("vertex_count was 0.")
		);

		return;
	}

	::glDrawArrays(
		sge::opengl::convert::primitive_type(
			_primitive_type
		),
		static_cast<
			GLsizei
		>(
			_first_vertex.get()
		),
		static_cast<
			GLint
		>(
			_num_vertices.get()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDrawArrays failed"),
		sge::renderer::exception
	)
}
