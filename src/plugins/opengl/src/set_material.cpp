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


#include <sge/opengl/set_material.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/material.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>


namespace
{

void
materialfv(
	GLenum const _face,
	GLenum const _type,
	GLfloat const *const _data
)
{
	::glMaterialfv(
		_face,
		_type,
		_data
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMaterialfv failed"),
		sge::renderer::exception
	)
}

void
materialf(
	GLenum const _face,
	GLenum const _type,
	GLfloat const _value
)
{
	::glMaterialf(
		_face,
		_type,
		_value
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMaterialf failed"),
		sge::renderer::exception
	)
}

void
material_color(
	GLenum const _face,
	GLenum const _type,
	sge::image::color::any::object const &_color
)
{
	materialfv(
		_face,
		_type,
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		).data()
	);
}

}

void
sge::opengl::set_material(
	renderer::material const &_material
)
{
	GLenum const face(
		GL_FRONT_AND_BACK
	);

	::material_color(
		face,
		GL_AMBIENT,
		_material.ambient().get()
	);

	::material_color(
		face,
		GL_DIFFUSE,
		_material.diffuse().get()
	);

	::material_color(
		face,
		GL_SPECULAR,
		_material.specular().get()
	);

	::material_color(
		face,
		GL_EMISSION,
		_material.emissive().get()
	);

	::materialf(
		face,
		GL_SHININESS,
		static_cast<
			GLfloat
		>(
			_material.shininess().get()
		)
	);
}
