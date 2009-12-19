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


#include "../matrix.hpp"
#include "../check_state.hpp"
#include "../glew.hpp"
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

class visitor {
public:
	typedef void result_type;

	result_type
	operator()(
		sge::fcppt::math::matrix::static_<float, 4, 4>::type const &m) const;

	result_type
	operator()(
		sge::fcppt::math::matrix::static_<double, 4, 4>::type const &m) const;
};

bool have_transpose()
{
	static bool const ret(
		sge::opengl::glew_is_supported(
			"GL_VERSION_1_3"
		)
	);

	return ret;
}

}

void sge::opengl::set_matrix(
	GLenum const mode,
	renderer::any_matrix const &mat)
{
	matrix_mode(mode);
	set_matrix(mat);
}

void sge::opengl::matrix_mode(
	GLenum const mode)
{
	glMatrixMode(mode);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMatrixMode failed"),
		sge::renderer::exception
	)
}

void sge::opengl::set_matrix(
	renderer::any_matrix const &mat)
{
	variant::apply_unary(
		visitor(),
		mat
	);
}

namespace
{

void visitor::operator()(
	sge::fcppt::math::matrix::static_<float, 4, 4>::type const &m) const
{
	if(have_transpose())
		glLoadTransposeMatrixf(
			m.data()
		);
	else
		glLoadMatrixf(
			sge::fcppt::math::matrix::transpose(
				m
			).data()
		);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glLoadMatrixf failed"),
		sge::renderer::exception
	)
}

void visitor::operator()(
	sge::fcppt::math::matrix::static_<double, 4, 4>::type const &m) const
{
	if(have_transpose())
		glLoadTransposeMatrixd(
			m.data()
		);
	else
		glLoadMatrixd(
			sge::fcppt::math::matrix::transpose(
				m
			).data()
		);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glLoadMatrixd failed"),
		sge::renderer::exception
	)
}

}
