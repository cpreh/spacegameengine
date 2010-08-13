/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../create_vertex_shader.hpp"
#include "../vertex_shader.hpp"
#include "../create_shader.hpp"

sge::renderer::glsl::vertex_shader_ptr const
sge::opengl::glsl::create_vertex_shader(
	opengl::context::object &_context,
	sge::renderer::glsl::string const &_source
)
{
	return
		opengl::glsl::create_shader<
			opengl::glsl::vertex_shader	
		>(
			_context,
			_source
		);
}
