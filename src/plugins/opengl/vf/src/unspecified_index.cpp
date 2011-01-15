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


#include "../unspecified_index.hpp"
#include "../../glsl/context.hpp"
#include "../../glsl/program_base.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/text.hpp>

GLint
sge::opengl::vf::unspecified_index(
	opengl::glsl::context &_context,
	sge::renderer::vf::string const &_name
)
{
	glsl::const_program_base_ptr const ptr(
		_context.active_program()
	);

	if(
		!ptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Tried to set a vertex_buffer that uses unspecified elements, ")
			FCPPT_TEXT("but a GLSL program is not set.")
			FCPPT_TEXT(" You have to set the GLSL program before setting the vertex buffer, ")
			FCPPT_TEXT("e.g. device->set_glsl_program(prog); device->set_vertex_buffer(buf);")
		);
	
	return
		ptr->location(
			fcppt::to_std_string(
				_name
			)
		);
}
