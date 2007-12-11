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


#include "../common.hpp"
#include "../default_render_target.hpp"

sge::ogl::default_render_target::default_render_target(const window_ptr wnd)
 : wnd(wnd)
{}

// FIXME: is this really intended (use the viewport dim here instead)?
sge::render_target::dim_type sge::ogl::default_render_target::dim() const
{
	return dim_type(wnd->width(), wnd->height());
}

sge::ogl::default_render_target::size_type sge::ogl::default_render_target::width() const
{
	return wnd->width();
}

sge::ogl::default_render_target::size_type sge::ogl::default_render_target::height() const
{
	return wnd->height();
}

sge::ogl::default_render_target::size_type sge::ogl::default_render_target::size() const
{
	return width()*height();
}

void sge::ogl::default_render_target::bind_me() const
{
	if(glBindFramebufferEXT)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
