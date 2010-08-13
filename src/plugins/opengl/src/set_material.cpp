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


#include "../set_material.hpp"
#include "../common.hpp"
#include "../check_state.hpp"
#include <sge/renderer/material.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

void
glmaterialfv(
	GLenum face,
	GLenum type,
	GLfloat const *
);

void
glmaterialf(
	GLenum face,
	GLenum type,
	GLfloat
);

void
material_color(
	GLenum face,
	GLenum type,
	sge::image::color::any::object const &
);

class arithmetic_visitor
{
public:
	typedef void result_type;

	arithmetic_visitor(
		GLenum face,
		GLenum type
	);

	template<
		typename T
	>
	result_type
	operator()(
		T
	) const;
private:
	GLenum const
		face_,
		type_;
};

}

void
sge::opengl::set_material(
	renderer::material const &_material
)
{
	GLenum const face = GL_FRONT_AND_BACK;

	::material_color(
		face,
		GL_AMBIENT,
		_material.ambient()
	);

	::material_color(
		face,
		GL_DIFFUSE,
		_material.diffuse()
	);

	::material_color(
		face,
		GL_SPECULAR,
		_material.specular()
	);

	::material_color(
		face,
		GL_EMISSION,
		_material.emissive()
	);

	fcppt::variant::apply_unary(
		::arithmetic_visitor(
			face,
			GL_SHININESS
		),
		_material.power()
	);
}

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
	glMaterialf(
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
	::materialfv(
		_face,
		_type,
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		).data()
	);
}

arithmetic_visitor::arithmetic_visitor(
	GLenum const _face,
	GLenum const _type
)
:
	face_(_face),
	type_(_type)
{}

template<
	typename T
>
void
arithmetic_visitor::operator()(
	T const _value
) const
{
	::materialf(
		face_,
		type_,
		static_cast<GLfloat>(
			_value
		)
	);

}

}
