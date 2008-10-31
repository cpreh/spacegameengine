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
along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../material.hpp"
#include "../common.hpp"
#include "../error.hpp"
#include <sge/renderer/material.hpp>
#include <sge/renderer/raw_color.hpp>
#include <sge/renderer/color_convert.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

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
	sge::renderer::any_color const &);

struct arithmetic_visitor : boost::static_visitor<> {
	arithmetic_visitor(
		GLenum face,
		GLenum type);
	
	template<
		typename T
	>
	void operator()(
		T) const;
private:
	GLenum const
		face,
		type;
};

}

void sge::ogl::set_material(
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

	boost::apply_visitor(
		arithmetic_visitor(
			face,
			GL_SHININESS),
		mat.power());
}

namespace
{

void glmaterialfv(
	GLenum const face,
	GLenum const type,
	GLfloat const *const data)
{
	SGE_OPENGL_SENTRY
	
	glMaterialfv(
		face,
		type,
		data);
}

void glmaterialf(
	GLenum const face,
	GLenum const type,
	GLfloat const f)
{
	SGE_OPENGL_SENTRY

	glMaterialf(
		face,
		type,
		f);
}

void material_color(
	GLenum const face,
	GLenum const type,
	sge::renderer::any_color const &color)
{
	glmaterialfv(
		face,
		type,
		sge::renderer::raw_color(
			sge::renderer::color_convert<sge::renderer::rgba_f32_color>(
				color)).data());
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
		static_cast<GLfloat>(f));
		
}

}
