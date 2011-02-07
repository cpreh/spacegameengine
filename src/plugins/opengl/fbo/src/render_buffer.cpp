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


#include "../render_buffer.hpp"
#include "../context.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo::render_buffer::render_buffer(
	fbo::context const &_context,
	GLenum const _internal_format,
	sge::renderer::dim2 const &_dim
)
:
	context_(_context),
	holder_(
		_context
	)
{
	bind();

	context_.renderbuffer_storage()(
		context_.renderbuffer_target(),
		_internal_format,
		static_cast<
			GLsizei
		>(
			_dim.w()
		),
		static_cast<
			GLsizei
		>(
			_dim.h()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Setting the storage of a render buffer failed."),
		sge::renderer::exception
	)

}

sge::opengl::fbo::render_buffer::~render_buffer()
{
}

GLuint
sge::opengl::fbo::render_buffer::id() const
{
	return holder_.id();
}

void
sge::opengl::fbo::render_buffer::bind() const
{
	context_.bind_renderbuffer()(
		context_.renderbuffer_target(),
		id()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a render buffer failed."),
		sge::renderer::exception
	)
}
