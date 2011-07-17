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


#include "../set_matrix.hpp"
#include "../check_state.hpp"
#include "../matrix_context.hpp"
#include "../context/use.hpp"
#include "../common.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::set_matrix(
	context::object &_context,
	renderer::matrix4 const &_matrix
)
{
	if(
		sge::opengl::context::use<
			sge::opengl::matrix_context
		>(
			_context
		).have_transpose()
	)
		::glLoadTransposeMatrixf(
			_matrix.data()
		);
	else
		::glLoadMatrixf(
			fcppt::math::matrix::transpose(
				_matrix
			).data()
		);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glLoadMatrixf failed"),
		sge::renderer::exception
	)
}
