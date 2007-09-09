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


#ifndef SGE_D3D_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_D3D_CUBE_TEXTURE_HPP_INCLUDED

#include "../../renderer/cube_texture.hpp"
#include "./resource.hpp"
#include "./texture_base.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class cube_texture : public d3d::texture_base, public sge::cube_texture, public resource {
	friend class renderer;
private:
	cube_texture(renderer* r, d3d_device_ptr device, const cube_side_array* data, size_type sz, resource_flag_t flags);
public:
	size_type size() const;
	resource_flag_t flags() const;
	void set_data(cube_side side, const_pointer p, const lock_rect* r = 0);
	void lock(cube_side side, const lock_rect* r = 0);
	void unlock();
private:
	void on_loss();
	void on_reset();

	void init(const cube_side_array* data = 0);

	d3d_device_ptr        device;
	d3d_cube_texture_ptr  tex;
	resource_flag_t       _flags;
	size_type             sz;
	pointer               lock_dest;
};

}
}

#endif
