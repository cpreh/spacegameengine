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
#include <sge/renderer/raw_color.hpp>
#include <sge/renderer/color_convert.hpp>
#include <sge/renderer/light.hpp>

namespace
{

void set_light_float_ptr(
	GLenum index,
	GLenum name,
	GLfloat const *data);

void set_light_pos(
	GLenum index,
	sge::math::vector4 const &);

void set_light_dir(
	GLenum index,
	sge::math::vector3 const &);

void set_light_float(
	GLenum index,
	GLenum name,
	GLfloat value);

void set_light_color(
	GLenum index,
	GLenum name,
	sge::renderer::any_color const &color);
}

void sge::ogl::set_light(
	renderer::light_index const index,
	renderer::light const &l)
{
	GLenum const glindex = convert_light_index(index);

	set_light_color(glindex, GL_AMBIENT, l.ambient);
	set_light_color(glindex, GL_DIFFUSE, l.diffuse);
	set_light_color(glindex, GL_SPECULAR, l.specular);

	math::vector4 const pos(
		l.pos,
		static_cast<math::vector4::value_type>(1));
	set_light_pos(glindex, pos);

	set_light_dir(glindex, l.dir);

	set_light_float(glindex, GL_CONSTANT_ATTENUATION, l.const_attenuation);
	set_light_float(glindex, GL_LINEAR_ATTENUATION, l.linear_attenuation);
	set_light_float(glindex, GL_QUADRATIC_ATTENUATION, l.quadratic_attenuation);

	set_light_float(glindex, GL_SPOT_EXPONENT, l.distribution_exponent);
	set_light_float(glindex, GL_SPOT_CUTOFF, l.cutoff_angle);

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

void set_light_pos(
	GLenum const index,
	sge::math::vector4 const &pos)
{
	set_light_float_ptr(index, GL_POSITION, pos.data());
}

void set_light_dir(
	GLenum const index,
	sge::math::vector3 const &dir)
{
	set_light_float_ptr(index, GL_SPOT_DIRECTION, dir.data());
}

void set_light_float(
	GLenum const index,
	GLenum const name,
	GLfloat const value)
{
	SGE_OPENGL_SENTRY
	
	glLightf(index, name, value);
}

void set_light_color(
	GLenum const index,
	GLenum const name,
	sge::renderer::any_color const &color)
{
	set_light_float_ptr(
		index,
		name,
		sge::renderer::raw_color(
			sge::renderer::color_convert<sge::renderer::rgba_f32_color>(
				color)).data());
}

}
