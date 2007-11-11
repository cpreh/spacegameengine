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


#ifndef SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_VOLUME_TEXTURE_HPP_INCLUDED

#include "../../renderer/volume_texture.hpp"
#include "common.hpp"
#include "basic_texture.hpp"

namespace sge
{
namespace ogl
{

namespace detail
{
typedef basic_texture<sge::volume_texture, GL_TEXTURE_3D> volume_texture_base;
}

class volume_texture : public detail::volume_texture_base {
public:
	volume_texture(const_pointer src,
	               size_type width,
	               size_type height,
	               size_type depth,
	               const filter_args& filter,
	               resource_flag_t flags);

	size_type size() const;
	size_type width() const;
	size_type height() const;
	size_type depth() const;

	void set_data(const_pointer src);
	void set_data(const_pointer src, const lock_box& b);
private:
	const size_type _width, _height, _depth;
};

}
}

#endif
