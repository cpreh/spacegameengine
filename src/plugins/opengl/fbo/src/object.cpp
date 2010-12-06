/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../object.hpp"
#include "../../fbo_context.hpp"
#include "../../check_state.hpp"
#include "../../bind_fbo.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo::object::object(
	fbo_context const &_context
)
:
	context_(_context)
{
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
		&id_
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenFramebuffers failed"),
		sge::renderer::exception
	)
}

sge::opengl::fbo::object::~object()
{
	context_.delete_framebuffers()(
		1,
		&id_
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteFramebuffers failed"),
		sge::renderer::exception
	)
}

void 
sge::opengl::fbo::object::bind() const
{
	opengl::bind_fbo(
		context_,
		id()
	);
}

GLuint
sge::opengl::fbo::object::id() const
{
	return id_;
}
