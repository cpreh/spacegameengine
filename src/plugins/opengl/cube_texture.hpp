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


#ifndef SGE_OPENGL_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_CUBE_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "basic_texture.hpp"
#include <sge/renderer/cube_texture.hpp>

#if defined(GLEW_VERSION_1_3)
#define SGE_OPENGL_CUBE_TEXTURE
#elif defined(GLEW_ARB_texture_cube_map)
#define SGE_OPENGL_CUBE_TEXTURE_ARB
#endif

#if defined(SGE_OPENGL_CUBE_TEXTURE) || defined(SGE_OPENGL_CUBE_TEXTURE_ARB)
#define SGE_OPENGL_HAVE_CUBE_TEXTURE
#endif

#ifdef SGE_OPENGL_HAVE_CUBE_TEXTURE

namespace sge
{
namespace ogl
{

namespace detail
{
#ifdef SGE_OPENGL_CUBE_TEXTURE
const GLenum cube_texture_type = GL_TEXTURE_CUBE_MAP;
#elif SGE_OPENGL_CUBE_TEXTURE_ARB
const GLenum cube_texture_type = CL_TEXTURE_CUBE_MAP_ARB;
#endif

typedef basic_texture<sge::cube_texture, cube_texture_type> cube_texture_base;
}

class cube_texture : public detail::cube_texture_base {
public:
	cube_texture(const cube_side_array* src,
	             size_type sz,
	             const filter_args& filter,
	             resource_flag_t flags);
	void set_data(cube_side::type side, const_pointer src, const lock_rect& r);
	void set_data(cube_side::type side, const_pointer src);
	size_type border_size() const;
private:
	const size_type sz;
};


}
}

#endif

#endif
