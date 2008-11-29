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


#ifndef SGE_OPENGL_FBO_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_TARGET_HPP_INCLUDED

#include "common.hpp"
#include "target.hpp"
#include "texture.hpp"
#include <sge/renderer/texture_fwd.hpp>

namespace sge
{
namespace ogl
{

class fbo_target : public target {
public:
	fbo_target();
	~fbo_target();

	void bind_texture(
		renderer::texture_ptr);	
	void bind_me() const;
private:
	dim_type const dim() const;

	size_type stride() const;
	GLenum format() const;
	GLenum format_type() const;

	texture_ptr           texture_target;
	GLuint                fbo;
};

}
}

#endif
