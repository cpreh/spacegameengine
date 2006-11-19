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


#ifndef SGE_D3D_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_D3D_VOLUME_TEXTURE_HPP_INCLUDED

#include "../../renderer/volume_texture.hpp"
#include "./resource.hpp"
#include "./texture_base.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer;

class volume_texture : public d3d::texture_base, public sge::volume_texture, public resource {
	friend class renderer;
private:
	volume_texture(renderer* r, d3d_device_ptr device, const_pointer src, size_type width, size_type height, size_type depth, resource_flag_t flags);
public:
	size_type width() const;
	size_type height() const;
	size_type depth() const;

	size_type size() const;
	void set_data(const_pointer src, const lock_box* b);

	resource_flag_t flags() const;

	void lock(const lock_box* b);
	void unlock();
private:
	void on_loss();
	void on_reset();

	void init();

	d3d_device_ptr          device;
	d3d_volume_texture_ptr  tex;
	d3d_volume_texture_ptr  temp_tex;
	pointer                 lock_dest;
	resource_flag_t         _flags;
	size_type               _width;
	size_type               _height;
	size_type               _depth;
};

}
}

#endif
