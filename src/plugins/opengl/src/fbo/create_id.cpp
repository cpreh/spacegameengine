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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/create_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>


sge::opengl::fbo::id const
sge::opengl::fbo::create_id(
	sge::opengl::fbo::context const &_context
)
{
	GLuint id;

	if(
		!_context.is_supported()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("glGenFrameBuffers"),
			FCPPT_TEXT("Opengl-3.0"),
			FCPPT_TEXT("frame_buffer_ext")
		);

	_context.gen_framebuffers()(
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenFramebuffers failed"),
		sge::renderer::exception
	)

	return
		sge::opengl::fbo::id(
			id
		);
}
