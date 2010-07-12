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


#include "../location.hpp"
#include "../../traits.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

template<
	bool Native
>
sge::opengl::glsl::traits<Native>::handle
location_impl(
	typename sge::opengl::glsl::traits<Native>::handle,
	char const *
);

template<>
sge::opengl::glsl::traits<true>::handle
location_impl(
	typename sge::opengl::glsl::traits<true>::handle const _program
	char const *const _name
)
{
	return
		glGetUniformLocation(
			_program,
			_name
		);
}

template<>
sge::opengl::glsl::traits<false>::handle
location_impl(
	typename sge::opengl::glsl::traits<false>::handle const _program
	char const *const _name
)
{
	return
		glGetUniformLocationARB(
			_program,
			_name
		);
}

}

template<
	bool Native
>
GLint
sge::opengl::glsl::uniform::location(
	typename traits<Native>::handle const program,
	char const *const name
)
{
	typename traits<Native>::handle const ret(
		location_impl(
			program,
			name
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetUniformLocation failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}
