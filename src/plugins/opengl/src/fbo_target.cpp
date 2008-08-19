/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../fbo_target.hpp"
#include "../version.hpp"
#include "../texture_base.hpp"
#include "../error.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::fbo_target::fbo_target(const dim_type& dim_)
 : dim_(dim_)
{
	if(!glGenFramebuffersEXT)
		on_not_supported(
			SGE_TEXT("glGenFrameBuffersEXT"),
			SGE_TEXT("none"),
			SGE_TEXT("frame_buffer_ext")
			);

	SGE_OPENGL_SENTRY

	glGenFramebuffersEXT(1, &fbo);
	bind_me();
}

sge::ogl::fbo_target::~fbo_target()
{
	glDeleteFramebuffersEXT(1, &fbo);
}

void sge::ogl::fbo_target::bind_me() const
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
}

void sge::ogl::fbo_target::bind_texture(const renderer::texture_ptr t)
{
	bind_me();
	const shared_ptr<texture_base> p(dynamic_pointer_cast<texture_base>(t));
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, p->id(), 0);
	const GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw exception(SGE_TEXT("glCheckFramebufferStatusEXT: fbo incomplete!"));
}

const sge::renderer::target::dim_type sge::ogl::fbo_target::dim() const
{
	return dim_;
}

sge::ogl::fbo_target::size_type
sge::ogl::fbo_target::stride() const
{
	return 4; // FIXME
}

GLenum sge::ogl::fbo_target::format() const
{
	return GL_RGBA; // FIXME
}

GLenum sge::ogl::fbo_target::format_type() const
{
	return GL_UNSIGNED_BYTE; // FIXME
}
