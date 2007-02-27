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


#ifndef SGE_OGL_TEXTURE_HPP_INCLUDED
#define SGE_OGL_TEXTURE_HPP_INCLUDED

#include "../../renderer/texture.hpp"
#include "common.hpp"
#include "basic_texture.hpp"

namespace sge
{
namespace ogl
{

class texture : public basic_texture<sge::texture,GL_TEXTURE_2D> {
public:
	texture(const_pointer src, size_type width, size_type height, const filter_args& filter, resource_flag_t flags);

	size_type width() const;
	size_type height() const;
	size_type size() const;

	void set_data(const_pointer src, const lock_rect* r = 0);
private:
	const size_type _width, _height;
};

}
}

#endif

