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


#include "../matrix_context.hpp"
#include "../context/make_id.hpp"
#include "../glew/is_supported.hpp"

sge::opengl::matrix_context::matrix_context()
:
	have_transpose_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_3"
		)
	)
{}

sge::opengl::matrix_context::~matrix_context()
{
}

bool
sge::opengl::matrix_context::have_transpose() const
{
	return have_transpose_;
}

sge::opengl::context::id const
sge::opengl::matrix_context::static_id(
	sge::opengl::context::make_id()
);
