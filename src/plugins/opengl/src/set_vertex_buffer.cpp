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


#include "../set_vertex_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../vertex_context.hpp"
#include "../vertex_declaration.hpp"
#include "../context/use.hpp"
#include <fcppt/dynamic_pointer_cast.hpp>

void
sge::opengl::set_vertex_buffer(
	opengl::context::object &_context,
	renderer::vf::dynamic::part_index const _index,
	renderer::const_vertex_buffer_ptr const _buffer
)
{
	opengl::vertex_context &context(
		opengl::context::use<
			opengl::vertex_context
		>(
			_context
		)
	);

	{
		opengl::const_vertex_buffer_ptr const old_buffer(
			context.vertex_buffer(
				_index
			)
		);

		if(
			old_buffer
		)
			old_buffer->unuse(
				context.vertex_declaration()->gl_format_part(
					_index
				)
			);
	}

	opengl::const_vertex_buffer_ptr const gl_buffer(
		fcppt::dynamic_pointer_cast<
			opengl::vertex_buffer const
		>(
			_buffer
		)
	);


	context.vertex_buffer(
		_index,
		gl_buffer
	);

	if(
		!gl_buffer
	)
		return;
	
	gl_buffer->use(
		context.vertex_declaration()->gl_format_part(
			_index
		)
	);
}
