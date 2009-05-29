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



#include "../variable_arb.hpp"
#include "../../../sentry.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
GLint sge::ogl::glsl::uniform::location<false>(
	traits<false>::handle const program,
	char const *const name)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetUniformLocationARB failed"),
		sge::renderer::glsl::exception
	)

	return glGetUniformLocationARB(
		program,
		name);
}
