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


#include <algorithm>
#include "../../../renderer/scoped_lock.hpp"
#include "../common.hpp"
#include "../cube_texture.hpp"
#include "../conversion.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"

template class sge::ogl::basic_texture<sge::cube_texture, GL_TEXTURE_CUBE_MAP>;

sge::ogl::cube_texture::cube_texture(const cube_side_array* const src,
                                     const size_type sz,
                                     const filter_args& filter,
                                     const resource_flag_t flags)
 : detail::cube_texture_base(filter, flags),
  sz(sz)
{
	if(src)
		set_cube_texture_data(*this,*src);
}


sge::ogl::cube_texture::size_type sge::ogl::cube_texture::size() const
{
	return border_size()*border_size();
}

sge::ogl::cube_texture::size_type sge::ogl::cube_texture::border_size() const
{
	return sz;
}

void sge::ogl::cube_texture::set_data(const cube_side::type side, const const_pointer src, const lock_rect& r)
{
	pre_setdata();
	//scoped_lock<sge::cube_texture*> lock_(this, lock_flags::writeonly);
	//std::copy(src, src + size(), data());
	set_texture_rect(convert_cast<GLenum>(side), filter(), border_size(), border_size(), r, src);
}

void sge::ogl::cube_texture::set_data(const cube_side::type side, const const_pointer src)
{
	pre_setdata();
	set_texture_rect(convert_cast<GLenum>(side), filter(), border_size(), border_size(), src);
}

/*void sge::ogl::cube_texture::lock(const cube_side::type side, const lock_flag_t lmode)
{
	
}*/
