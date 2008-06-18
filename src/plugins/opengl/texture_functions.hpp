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


#ifndef SGE_OPENGL_TEXTURE_FUNCTIONS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCTIONS_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/types.hpp>

namespace sge
{
namespace ogl
{

GLuint gen_texture();
void delete_texture(GLuint id);

typedef unsigned char *texture_pointer;
typedef unsigned char const *const_texture_pointer;

void set_texture(
	GLenum target,
	GLenum format,
	GLenum type,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& dim,
	const_texture_pointer src);

void build_mipmaps(
	GLenum target,
	GLenum format,
	GLenum type,
	const renderer::texture::dim_type& dim,
	const_texture_pointer src);

void set_texture_rect(
	GLenum target,
	GLenum format,
	GLenum type,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& dim,
	const renderer::lock_rect& dest,
	const_texture_pointer src);

void read_pixels(
	GLenum format,
	GLenum type,
	renderer::texture_base::size_type x,
	renderer::texture_base::size_type y,
	renderer::texture_base::size_type width,
	renderer::texture_base::size_type height,
	texture_pointer dest);

void get_tex_image(
	GLenum format,
	GLenum type,
	texture_pointer dest);

void tex_parameter_i(
	GLenum type,
	GLenum name,
	GLint value);

void bind_texture(
	GLenum type,
	GLuint value);

void set_texture_filter(
	GLenum type,
	const renderer::filter_args& filter);

}
}

#endif
