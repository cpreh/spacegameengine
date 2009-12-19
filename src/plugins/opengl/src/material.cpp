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


#include "../material.hpp"
#include "../common.hpp"
#include "../check_state.hpp"
#include <sge/renderer/material.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/text.hpp>

namespace
{

void glmaterialfv(
	GLenum face,
	GLenum type,
	GLfloat const *);

void glmaterialf(
	GLenum face,
	GLenum type,
	GLfloat);

void material_color(
	GLenum face,
	GLenum type,
	sge::image::color::any::object const &);

class arithmetic_visitor {
public:
	typedef void result_type;

	arithmetic_visitor(
		GLenum face,
		GLenum type);

	template<
		typename T
	>
	result_type
	operator()(
		T) const;
private:
	GLenum const
		face,
		type;
};

}

void sge::opengl::set_material(
	renderer::material const &mat)
{
	GLenum const face = GL_FRONT_AND_BACK;

	material_color(
		face,
		GL_AMBIENT,
		mat.ambient());

	material_color(
		face,
		GL_DIFFUSE,
		mat.diffuse());

	material_color(
		face,
		GL_SPECULAR,
		mat.specular());

	material_color(
		face,
		GL_EMISSION,
		mat.emissive());

	variant::apply_unary(
		arithmetic_visitor(
			face,
			GL_SHININESS
		),
		mat.power()
	);
}

namespace
{

void glmaterialfv(
	GLenum const face,
	GLenum const type,
	GLfloat const *const data)
{
	glMaterialfv(
		face,
		type,
		data
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMaterialfv failed"),
		sge::renderer::exception
	)
}

void glmaterialf(
	GLenum const face,
	GLenum const type,
	GLfloat const f)
{
	glMaterialf(
		face,
		type,
		f
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMaterialf failed"),
		sge::renderer::exception
	)
}

void material_color(
	GLenum const face,
	GLenum const type,
	sge::image::color::any::object const &color)
{
	glmaterialfv(
		face,
		type,
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			color
		).data()
	);
}

arithmetic_visitor::arithmetic_visitor(
	GLenum const face,
	GLenum const type)
:
	face(face),
	type(type)
{}

template<
	typename T
>
void arithmetic_visitor::operator()(
	T const f) const
{
	glmaterialf(
		face,
		type,
		static_cast<GLfloat>(f)
	);

}

}
