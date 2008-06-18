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

namespace sge
{
namespace ogl
{

namespace detail
{

typedef basic_texture<renderer::cube_texture> cube_texture_base;

}

class cube_texture : public detail::cube_texture_base {
public:
	cube_texture(
		const cube_side_array* src,
		size_type sz,
		const renderer::filter_args& filter,
		resource_flag_type flags);
	void set_data(
		renderer::cube_side::type side,
		const_pointer src,
		const renderer::lock_rect& r);
	void set_data(
		renderer::cube_side::type side,
		const_pointer src);
	size_type border_size() const;
private:
	const size_type sz;
};

GLenum convert_cast(const renderer::cube_side::type&);

}
}

#endif
