/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED

#include "basic_texture.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/volume_texture.hpp>

namespace sge
{
namespace d3d9
{

namespace detail
{

typedef basic_texture<sge::volume_texture> volume_texture_base_type;

}

class renderer;

class volume_texture : public detail::volume_texture_base_type {
public:
	volume_texture(
		renderer& r,
		d3d_device_ptr device,
		const_pointer src,
		const box_type& box,
		const filter_args& filter,
		resource_flag_t flags);

	const box_type box() const;
	void set_data(const_pointer src);
	void set_data(const_pointer src, const lock_box& b);

	void lock(lock_flag_t lflags);
	void lock(const lock_box&, lock_flag_t lflags);
	void unlock();

	pointer data();
	const_pointer data() const;
private:
	void lock(const lock_box* b, lock_flag_t lflags);
	void do_loss();
	IDirect3DBaseTexture9* do_reset();

	d3d_device_ptr          device;
	d3d_volume_texture_ptr  tex;
	d3d_volume_texture_ptr  temp_tex;
	pointer                 lock_dest;
	box_type                box_;
};

}
}

#endif
