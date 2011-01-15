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


#include "../tex_envf_ext.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

void
tex_env_f(
	GLenum const type,
	GLenum const arg,
	GLfloat const value
)
{
	glTexEnvf(
		type,
		arg,
		value
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexEnvf failed"),
		sge::renderer::exception
	)
}

}

void
sge::opengl::tex_envf_ext(
	GLenum const arg,
	GLenum const value
)
{
	tex_env_f(
		GL_TEXTURE_ENV,
		GL_TEXTURE_ENV_MODE,
		GL_COMBINE
	);

	tex_env_f(
		GL_TEXTURE_ENV,
		arg,
		static_cast<GLfloat>(value)
	);
}
