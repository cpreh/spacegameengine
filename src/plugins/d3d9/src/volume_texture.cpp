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


#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../texture_functions.hpp"
#include <sge/exception.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/algorithm.hpp>

sge::d3d9::volume_texture::volume_texture(
	renderer& r,
  const d3d_device_ptr device,
	const const_pointer src,
	const box_type& box_,
	const filter_args& filter,
	const resource_flag_t flags)
: detail::volume_texture_base_type(r, filter, flags),
  device(device),
  lock_dest(0),
	box_(box_)
{
	on_reset();
	if(src)
		set_data(src);
}

IDirect3DBaseTexture9* sge::d3d9::volume_texture::do_reset()
{
	tex.reset(
		create_volume_texture(
			device,
			box(),
			filter(),
			flags(),
			false));
	return tex.get();
}

void sge::d3d9::volume_texture::lock(const lock_flag_t lflags)
{
	lock(0, lflags);
}

void sge::d3d9::volume_texture::lock(const lock_box& b, const lock_flag_t lflags)
{
	lock(&b, lflags);
}

void sge::d3d9::volume_texture::lock(const lock_box* const b, const lock_flag_t lflags)
{
	if(flags() & resource_flags::dynamic)
		lock_dest = lock_volume_texture(tex, b, lflags, flags());
	else
	{
		temp_tex.reset(
			create_volume_texture(
				device,
				box(),
				filter(),
				flags(),
				true));
		lock_dest = lock_volume_texture(tex, b, lflags, flags());
	}
}

void sge::d3d9::volume_texture::unlock()
{
	if(flags() & resource_flags::dynamic)
		unlock_volume_texture(tex);
	else
	{
		unlock_volume_texture(temp_tex);
		update_texture(device, temp_tex.get(), tex.get());
		temp_tex.reset();
	}
	lock_dest = 0;
}

sge::volume_texture::pointer sge::d3d9::volume_texture::data()
{
	return lock_dest;
}

sge::volume_texture::const_pointer sge::d3d9::volume_texture::data() const
{
	return lock_dest;
}

void sge::d3d9::volume_texture::do_loss()
{
	tex.reset();
}

void sge::d3d9::volume_texture::set_data(const const_pointer data)
{
	const scoped_lock<volume_texture*> l(make_scoped_lock(this, lock_flags::writeonly));
	copy_n(data, size(), lock_dest);
}

void sge::d3d9::volume_texture::set_data(const const_pointer data, const lock_box& b)
{
	//const scoped_lock<volume_texture*> l(make_scoped_lock(this, b, lock_flags::writeonly));
	//copy_n(data, b.size(), lock_dest);
}

const sge::volume_texture::box_type sge::d3d9::volume_texture::box() const
{
	return box_;
}
