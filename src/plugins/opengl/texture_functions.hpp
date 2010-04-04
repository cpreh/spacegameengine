/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>

namespace sge
{
namespace opengl
{

GLuint gen_texture();
void delete_texture(GLuint id);

void set_texture(
	GLenum target,
	GLenum format,
	GLenum type,
	renderer::filter::texture const &filter,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer src);

void build_mipmaps(
	GLenum target,
	GLenum format,
	GLenum type,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer src);

void set_texture_rect(
	GLenum target,
	GLenum format,
	GLenum type,
	renderer::filter::texture const &filter,
	renderer::dim_type const &dim,
	renderer::lock_rect const &dest,
	renderer::const_raw_pointer src);

void get_tex_image(
	GLenum format,
	GLenum type,
	renderer::raw_pointer dest);

void tex_parameter_i(
	GLenum type,
	GLenum name,
	GLint value);

void bind_texture(
	GLenum type,
	GLuint value);

void set_texture_filter(
	GLenum type,
	renderer::filter::texture const &);

}
}

#endif
