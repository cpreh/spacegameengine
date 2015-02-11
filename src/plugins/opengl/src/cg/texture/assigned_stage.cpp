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


#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/cg/texture/assigned_stage.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::texture::stage const
sge::opengl::cg::texture::assigned_stage(
	sge::cg::parameter::object const &_parameter
)
{
	GLenum const ret(
		::cgGLGetTextureEnum(
			_parameter.get()
		)
	);

	if(
		ret
		==
		GL_INVALID_OPERATION
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgGLGetTextureEnum failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLGetTextureEnum failed"),
		sge::renderer::exception
	);

	FCPPT_ASSERT_ERROR(
		ret >= GL_TEXTURE0_ARB
	);

	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::stage,
			fcppt::cast::static_cast_fun
		>(
			ret
			-
			GL_TEXTURE0_ARB
		);
}
