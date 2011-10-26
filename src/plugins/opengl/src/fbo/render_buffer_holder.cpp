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


#include <sge/opengl/fbo/render_buffer_holder.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::opengl::fbo::render_buffer_holder::render_buffer_holder(
	fbo::context const &_context
)
:
	context_(_context),
	id_()
{
	context_.gen_renderbuffers()(
		1,
		&id_
	);
	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Generating a render buffer failed."),
		sge::renderer::exception
	)
}

sge::opengl::fbo::render_buffer_holder::~render_buffer_holder()
{
	context_.delete_renderbuffers()(
		1,
		&id_
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Deleting a render buffer failed."),
		sge::renderer::exception
	)
}

GLuint
sge::opengl::fbo::render_buffer_holder::id() const
{
	return id_;
}
