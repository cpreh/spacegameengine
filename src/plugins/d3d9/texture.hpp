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


#ifndef SGE_D3D9_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_HPP_INCLUDED

#include "../../renderer/texture.hpp"
#include "basic_texture.hpp"
#include "d3dinclude.hpp"

namespace sge
{
namespace d3d9
{

class renderer;

class texture : public basic_texture<sge::texture> {
	friend class renderer;
private:
	texture(renderer& r, d3d_device_ptr device, const_pointer data, size_type width, size_type height, const filter_args& filter, resource_flag_t flags);
public:
	size_type width() const;
	size_type height() const;
	size_type size() const;
	
	void set_data(const_pointer data);	
	void set_data(const_pointer data, const lock_rect& r);
	
	resource_flag_t flags() const;

	void lock();
	void lock(const lock_rect&);
	void unlock();

	void filter(const filter_args&);
private:
	void lock(const lock_rect* r);

	void on_loss();
	IDirect3DBaseTexture9* on_reset();

	d3d_device_ptr   device;
	d3d_texture_ptr  tex;
	d3d_texture_ptr  temp_tex;
	size_type        _width;
	size_type        _height;
	pointer          lock_dest;
};

}
}

#endif
