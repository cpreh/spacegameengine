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


#include "../matrix.hpp"
#include "../error.hpp"
#include "../glew.hpp"
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/matrix/static.hpp>
#include <sge/math/matrix/transpose.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

namespace
{

class visitor : public boost::static_visitor<> {
public:
	void operator()(
		sge::math::matrix::static_<float, 4, 4>::type const &m) const;
	void operator()(
		sge::math::matrix::static_<double, 4, 4>::type const &m) const;
};

bool have_transpose()
{
	static bool const ret(
		sge::ogl::glew_is_supported(
			"GL_VERSION_1_3"
		)
	);

	return ret;
}

}

void sge::ogl::set_matrix(
	GLenum const mode,
	renderer::any_matrix const &mat)
{
	matrix_mode(mode);
	set_matrix(mat);
}

void sge::ogl::matrix_mode(
	GLenum const mode)
{
	SGE_OPENGL_SENTRY
	glMatrixMode(mode);
}

void sge::ogl::set_matrix(
	renderer::any_matrix const &mat)
{
	boost::apply_visitor(
		visitor(),
		mat);
}

namespace
{

void visitor::operator()(
	sge::math::matrix::static_<float, 4, 4>::type const &m) const
{
	SGE_OPENGL_SENTRY

	if(have_transpose())
		glLoadTransposeMatrixf(
			m.data()
		);
	else
		glLoadMatrixf(
			sge::math::matrix::transpose(
				m
			).data()
		);
}
	
void visitor::operator()(
	sge::math::matrix::static_<double, 4, 4>::type const &m) const
{
	SGE_OPENGL_SENTRY

	if(have_transpose())
		glLoadTransposeMatrixd(
			m.data()
		);
	else
		glLoadMatrixd(
			sge::math::matrix::transpose(
				m
			).data()
		);

}

}
