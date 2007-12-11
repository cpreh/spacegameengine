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


#include "../../../exception.hpp"
#include "../fbo_render_target.hpp"
#include "../extension.hpp"
#include "../texture_base.hpp"

sge::ogl::fbo_render_target::fbo_render_target(const dim_type& dim_)
 : dim_(dim_)
{
	if(!glGenFramebuffersEXT)
		throw exception(extension_not_supported_string("frame_buffer_ext"));
	glGenFramebuffersEXT(1, &fbo);
	bind_me();

	if(!glGenRenderbuffersEXT)
		throw exception(extension_not_supported_string("render_buffer_ext"));
	glGenRenderbuffersEXT(1, &depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, static_cast<GLsizei>(width()), static_cast<GLsizei>(height()));
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
}

sge::ogl::fbo_render_target::~fbo_render_target()
{
	glDeleteFramebuffersEXT(1, &fbo);
	glDeleteRenderbuffersEXT(1, &depthbuffer);
}

void sge::ogl::fbo_render_target::bind_me() const
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
}

sge::render_target::dim_type sge::ogl::fbo_render_target::dim() const
{
	return dim_;
}

sge::ogl::fbo_render_target::size_type sge::ogl::fbo_render_target::width() const
{
	return dim().w();
}

sge::ogl::fbo_render_target::size_type sge::ogl::fbo_render_target::height() const
{
	return dim().h();
}

sge::ogl::fbo_render_target::size_type sge::ogl::fbo_render_target::size() const
{
	return width() * height();
}

void sge::ogl::fbo_render_target::bind_texture(const texture_ptr t)
{
	bind_me();
	const shared_ptr<texture_base> p(dynamic_pointer_cast<texture_base>(t));
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, p->id(), 0);
	const GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw exception("glCheckFramebufferStatusEXT: fbo incomplete!");
}
