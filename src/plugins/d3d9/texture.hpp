/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_D3D9_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_HPP_INCLUDED

#include "basic_texture.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/texture.hpp>

namespace sge
{
namespace d3d9
{

class renderer;

namespace detail
{

typedef basic_texture<sge::texture> texture_base_type;

}

class texture : public detail::texture_base_type {
public:
	texture(
		renderer& r,
		d3d_device_ptr device,
		const_pointer data,
		const dim_type& dim,
		const filter_args& filter,
		resource_flag_t flags);
	
	const dim_type dim() const;
	
	void set_data(const_pointer data);	
	void set_data(const_pointer data, const lock_rect& r);
	
	void lock(lock_flag_t);
	void lock(const lock_rect&, lock_flag_t);
	void unlock();

	pointer data();
	const_pointer data() const;
private:
	void lock(const lock_rect* r, lock_flag_t);

	void do_loss();
	IDirect3DBaseTexture9* do_reset();

	d3d_device_ptr   device;
	d3d_texture_ptr  tex;
	d3d_texture_ptr  temp_tex;
	dim_type         dim_;
	pointer          lock_dest;
};

}
}

#endif
