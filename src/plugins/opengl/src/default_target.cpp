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
#include "../default_target.hpp"

sge::ogl::default_target::default_target(
	dim_type const & dim_)
 : dim_(dim_)
{}

sge::renderer::target::dim_type const 
sge::ogl::default_target::dim() const
{
	return dim_;
}

void sge::ogl::default_target::bind_me() const
{
	// TODO: this should be somewhere else!
	if(glBindFramebufferEXT)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

sge::ogl::default_target::size_type
sge::ogl::default_target::stride() const
{
	return 4; // FIXME
}

GLenum sge::ogl::default_target::format() const
{
	return GL_RGBA; // FIXME
}

GLenum sge::ogl::default_target::format_type() const
{
	return GL_UNSIGNED_BYTE; // FIXME
}
