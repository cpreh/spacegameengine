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


#include "../set_light.hpp"
#include "../check_state.hpp"
#include "../vector4f.hpp"
#include "../convert/light_index.hpp"
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/renderer/vector_convert.hpp>
#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/renderer/light.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

void light_float_ptr(
	GLenum index,
	GLenum name,
	GLfloat const *data);

void light_float(
	GLenum index,
	GLenum name,
	GLfloat value);

void light_arithmetic(
	GLenum index,
	GLenum name,
	sge::renderer::any_arithmetic const &);

void light_pos(
	GLenum index,
	sge::renderer::any_vector3 const &);

void light_dir(
	GLenum index,
	sge::renderer::any_vector3 const &);

void light_color(
	GLenum index,
	GLenum name,
	sge::image::color::any::object const &color);
}

void
sge::opengl::set_light(
	renderer::light_index const index,
	renderer::light const &l
)
{
	GLenum const glindex = convert::light_index(index);

	light_color(glindex, GL_AMBIENT, l.ambient());
	light_color(glindex, GL_DIFFUSE, l.diffuse());
	light_color(glindex, GL_SPECULAR, l.specular());

	light_pos(glindex, l.position());

	light_dir(glindex, l.direction());

	light_arithmetic(glindex, GL_CONSTANT_ATTENUATION, l.const_attenuation());
	light_arithmetic(glindex, GL_LINEAR_ATTENUATION, l.linear_attenuation());
	light_arithmetic(glindex, GL_QUADRATIC_ATTENUATION, l.quadratic_attenuation());

	light_arithmetic(glindex, GL_SPOT_EXPONENT, l.distribution_exponent());
	light_arithmetic(glindex, GL_SPOT_CUTOFF, l.cutoff_angle());

}

namespace
{

void
light_float_ptr(
	GLenum const index,
	GLenum const name,
	GLfloat const *const data
)
{

	glLightfv(index, name, data);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glLightfv failed"),
		sge::renderer::exception
	)

}

void
light_float(
	GLenum const index,
	GLenum const name,
	GLfloat const value
)
{
	glLightf(index, name, value);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glLightf failed"),
		sge::renderer::exception
	)
}

void
light_arithmetic(
	GLenum const index,
	GLenum const name,
	sge::renderer::any_arithmetic const &value
)
{
	light_float(
		index,
		name,
		sge::renderer::arithmetic_convert<
			GLfloat
		>(
			value
		)
	);
}

void
light_pos(
	GLenum const index,
	sge::renderer::any_vector3 const &pos
)
{
	sge::opengl::vector4f const pos4(
		fcppt::math::vector::construct(
			sge::renderer::vector_convert<
				GLfloat,
				3
			>(
				pos
			),
			static_cast<GLfloat>(1)
		)
	);

	light_float_ptr(
		index,
		GL_POSITION,
		pos4.data());
}

void
light_dir(
	GLenum const index,
	sge::renderer::any_vector3 const &dir
)
{
	light_float_ptr(
		index,
		GL_SPOT_DIRECTION,
		sge::renderer::vector_convert<
			GLfloat,
			3
		>(
			dir
		).data()
	);
}

void
light_color(
	GLenum const index,
	GLenum const name,
	sge::image::color::any::object const &color
)
{
	light_float_ptr(
		index,
		name,
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			color
		).data()
	);
}

}
