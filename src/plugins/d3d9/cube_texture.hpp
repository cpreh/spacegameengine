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


#ifndef SGE_D3D9_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_CUBE_TEXTURE_HPP_INCLUDED

#include "../../renderer/cube_texture.hpp"
#include "basic_texture.hpp"
#include "d3dinclude.hpp"

namespace sge
{
namespace d3d9
{

namespace detail
{

typedef basic_texture<sge::cube_texture> cube_texture_base_type;

}

class cube_texture : public detail::cube_texture_base_type {
	friend class renderer;
private:
	cube_texture(renderer& r,
	             d3d_device_ptr device,
	             const cube_side_array* data,
	             size_type sz,
	             const filter_args& filter,
	             resource_flag_t flags);
public:
	size_type size() const;
	size_type border_size() const;

	void set_data(cube_side::type side, const_pointer p);
	void set_data(cube_side::type side, const_pointer p, const lock_rect& r);

	void lock(cube_side::type side);
	void lock(cube_side::type side, const lock_rect&);
	void unlock();
private:
	void lock(cube_side::type side, const lock_rect* r);
	void do_loss();
	IDirect3DBaseTexture9* do_reset();

	void init(const cube_side_array* data = 0);

	d3d_device_ptr        device;
	d3d_cube_texture_ptr  tex;
	size_type             sz;
	pointer               lock_dest;
};

}
}

#endif
