/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_RENDER_TARGET_HPP_INCLUDED
#define SGE_OGL_RENDER_TARGET_HPP_INCLUDED

#include "./common.hpp"
#include "./texture_base.hpp"
#include "../../renderer/render_target.hpp"

namespace sge
{
namespace ogl
{

class render_target : public sge::render_target, public texture_base {
public:
	render_target(size_type width, size_type height);
	~render_target();
	size_type width() const;
	size_type height() const;
	size_type size() const;
	resource_flag_t flags() const;

	void bind_texture(texture_ptr);	
	GLuint id() const;
	void bind_me() const;
private:
	size_type _width,
	          _height;

	GLuint    fbo;
	GLuint    depthbuffer;
};

typedef shared_ptr<render_target> render_target_ptr;

}
}

#endif
