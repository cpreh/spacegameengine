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
#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::fbo::attach_texture_2d(
	sge::opengl::fbo::context const &_context,
	sge::opengl::fbo::attachment_type const _attachment,
	sge::opengl::texture::buffer_type const _texture_type,
	sge::opengl::texture::id const _texture_id,
	sge::renderer::texture::mipmap::level const _level
)
{
	_context.framebuffer_texture_2d()(
		*_context.framebuffer_target(),
		_attachment.get(),
		_texture_type.get(),
		_texture_id.get(),
		static_cast<
			GLint
		>(
			_level.get()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a texture to an fbo failed."),
		sge::renderer::exception
	)
}
