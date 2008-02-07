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
#include "../volume_texture.hpp"
#ifdef SGE_OPENGL_HAVE_VOLUME_TEXTURE
#include "../../../stub.hpp"
#include "../../../math/box_impl.hpp"
#include "../error.hpp"
#include "../basic_texture_impl.hpp"

template class sge::ogl::basic_texture<sge::volume_texture, sge::ogl::detail::volume_texture_type>;

sge::ogl::volume_texture::volume_texture(const const_pointer src,
                                         const box_type& box_,
                                         const filter_args& filter,
                                         const resource_flag_t flags)
 : detail::volume_texture_base(filter, flags),
   box_(box_)
{
	set_data(src);
}

sge::ogl::volume_texture::box_type sge::ogl::volume_texture::box() const
{
	return box_;
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::size() const
{
	return width()*height()*depth();
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::width() const
{
	return box().w();
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::height() const
{
	return box().h();
}

sge::ogl::volume_texture::size_type sge::ogl::volume_texture::depth() const
{
	return box().d();
}

void sge::ogl::volume_texture::set_data(const const_pointer src)
{
	pre_setdata();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;

	SGE_OPENGL_SENTRY

#ifdef SGE_OPENGL_VOLUME_TEXTURE
	glTexImage3D(
#elif SGE_OPENGL_VOLUME_TEXTURE_EXT
	glTexImage3DEXT(
#endif
	             detail::volume_texture_type,
	             0,
	             4,
	             static_cast<GLsizei>(width()),
	             static_cast<GLsizei>(height()),
	             static_cast<GLsizei>(depth()),
	             0,
	             format,
	             type,
	             src);
}

void sge::ogl::volume_texture::set_data(const const_pointer src, const lock_box& b)
{
#ifdef SGE_OPENGL_VOLUME_TEXTURE
	pre_setdata();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;

	SGE_OPENGL_SENTRY

	glTexSubImage3D(detail::volume_texture_type,
	                0,
	                static_cast<GLint>(b.left()),
	                static_cast<GLint>(b.top()),
	                static_cast<GLint>(b.front()),
	                static_cast<GLsizei>(b.w()),
	                static_cast<GLsizei>(b.h()),
	                static_cast<GLsizei>(b.d()),
	                format,
	                type,
	                src);
#else
	SGE_STUB_FUNCTION
#endif
}

#endif
