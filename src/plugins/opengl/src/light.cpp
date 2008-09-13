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


#include "../light.hpp"
#include "../error.hpp"

namespace
{

void set_light_float_ptr(
	GLenum index,
	GLenum name,
	GLfloat const *data);

}

void sge::ogl::set_light_colorf(
	GLenum const index,
	GLenum const name,
	renderer::any_color const &color)
{
	// FIXME:
	//set_light_float_ptr(index, name, reinterpret_cast<const GLfloat*>(&color));
}

void sge::ogl::set_light_pos(
	GLenum const index,
	math::vector4 const &pos)
{
	set_light_float_ptr(index, GL_POSITION, pos.data());
}

void sge::ogl::set_light_dir(
	GLenum const index,
	math::vector3 const &dir)
{
	set_light_float_ptr(index, GL_SPOT_DIRECTION, dir.data());
}

void sge::ogl::set_light_float(
	GLenum const index,
	GLenum const name,
	GLfloat const value)
{
	SGE_OPENGL_SENTRY
	
	glLightf(index, name, value);
}

GLenum sge::ogl::convert_light_index(
	renderer::light_index const index)
{
	return GL_LIGHT0 + index;
}

namespace
{

void set_light_float_ptr(
	GLenum const index,
	GLenum const name,
	GLfloat const *const data)
{
	SGE_OPENGL_SENTRY
	
	glLightfv(index, name, data);
}

}


