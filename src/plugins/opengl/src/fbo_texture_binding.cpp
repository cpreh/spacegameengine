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


#include "../fbo_texture_binding.hpp"
#include "../fbo.hpp"
#include "../fbo_context.hpp"
#include "../texture.hpp"
#include "../texture_base.hpp"
#include "../check_state.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo_texture_binding::fbo_texture_binding(
	fbo_context const &_context,
	opengl::texture_base_ptr const _texture,
	fbo &_fbo,
	GLenum const _attachment
)
:
	texture_(_texture)
{
	_fbo.bind();

	_context.framebuffer_texture_2d()(
		_context.framebuffer_target(),
		_attachment,
		GL_TEXTURE_2D,
		_texture->id(),
		0
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a texture to an fbo failed."),
		sge::renderer::exception
	)
}

sge::opengl::fbo_texture_binding::~fbo_texture_binding()
{
}
