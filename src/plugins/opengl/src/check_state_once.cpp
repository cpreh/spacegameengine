/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/check_state_always.hpp>
#include <sge/opengl/check_state_once.hpp>
#if !defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
#include <sge/renderer/exception.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/error_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#endif


void
sge::opengl::check_state_once()
{
#if !defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
	GLenum ret(
		GL_NO_ERROR
	);

	fcppt::string errors;

	while(
		(
			ret
			=
			sge::opengl::call(
				::glGetError
			)
		)
		!= GL_NO_ERROR
	)
		errors +=
			sge::opengl::error_string(
				ret
			)
			+
			FCPPT_TEXT(", ");

	if(
		ret != GL_NO_ERROR
	)
	{
		// erase last ", "
		errors.erase(
			errors.end() - 2,
			errors.end()
		);

		throw sge::renderer::exception(
			FCPPT_TEXT("Cumulative GL errors: ")
			+ errors
		);
	}
#endif
}
