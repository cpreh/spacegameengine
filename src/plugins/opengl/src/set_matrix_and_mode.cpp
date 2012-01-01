/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/matrix_mode.hpp>
#include <sge/opengl/set_matrix.hpp>
#include <sge/opengl/set_matrix_and_mode.hpp>
#include <sge/opengl/convert/matrix_mode.hpp>
#include <sge/opengl/convert/projection.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>


void
sge::opengl::set_matrix_and_mode(
	context::object &_context,
	renderer::matrix_mode::type const _mode,
	renderer::matrix4 const &_matrix
)
{
	opengl::matrix_mode(
		convert::matrix_mode(
			_mode
		)
	);

	opengl::set_matrix(
		_context,
		_mode == renderer::matrix_mode::projection
		?
			convert::projection(
				_matrix
			)
		:
			_matrix
	);
}
