/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#if 0
#include "../../../exception.hpp"
#include "../program.hpp"

sge::ogl::program::program()
: id_(glCreateProgram())
{}

sge::ogl::program::~program()
{
	for(shader_vector::iterator it = shaders.begin(); it != shaders.end(); ++it)
		glDetachShader(id(), (*it)->id());
	glDeleteProgram(id());
}

void sge::ogl::program::attach_shader(const shader_ptr s)
{
	glAttachShader(id(), s->id());
	shaders.push_back(s);
}

void sge::ogl::program::link()
{
	glLinkProgram(id());

	int link_status;
	glGetProgramiv(id(), GL_LINK_STATUS, &link_status);
	if(link_status == GL_FALSE)
		throw exception("Linking a program failed!");
}

void sge::ogl::program::use()
{
	glUseProgram(id());
}

GLuint sge::ogl::program::id() const
{
	return id_;
}
#endif
