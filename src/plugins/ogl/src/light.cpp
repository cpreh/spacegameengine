/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../exception.hpp"
#include "../light.hpp"
#include "../error.hpp"

namespace
{

void set_light_float_ptr(const GLenum index, const GLenum name, const GLfloat* const data)
{
	glLightfv(index, name, data);
	if(sge::ogl::is_error())
		throw sge::exception("glLightfv() failed!");
}

}

void sge::ogl::set_light_color4(const GLenum index, const GLenum name, const color4& color)
{
	set_light_float_ptr(index, name, reinterpret_cast<const GLfloat*>(&color));
}

void sge::ogl::set_light_pos(const GLenum index, const math::vector4& pos)
{
	set_light_float_ptr(index, GL_POSITION, pos.data());
}

void sge::ogl::set_light_dir(const GLenum index, const math::vector3& dir)
{
	set_light_float_ptr(index, GL_SPOT_DIRECTION, dir.data());
}

void sge::ogl::set_light_float(const GLenum index, const GLenum name, const GLfloat value)
{
	glLightf(index, name, value);
	if(is_error())
		throw exception("glLightf() failed!");

}

GLenum sge::ogl::convert_light_index(const light_index index)
{
	return GL_LIGHT0 + index;
}
