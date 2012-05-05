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


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/texture/bind_type.hpp>
#include <sge/opengl/texture/get_binding.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


sge::opengl::texture::optional_id const
sge::opengl::texture::get_binding(
	sge::opengl::texture::bind_type const _binding
)
{
	GLint const ret(
		sge::opengl::get_int(
			_binding.get()
		)
	);

	return
		ret
		==
		0
		?
			sge::opengl::texture::optional_id()
		:
			sge::opengl::texture::optional_id(
				fcppt::strong_typedef_construct_cast<
					sge::opengl::texture::id
				>(
					ret
				)
			)
		;
}
