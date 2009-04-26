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



#include "../texture.hpp"
#include "../texture_functions.hpp"
#include "../conversion.hpp"
#include <sge/algorithm.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/exception.hpp>

sge::d3d9::texture::texture(
	renderer& r,
	const d3d_device_ptr device,
	const const_pointer data,
	const dim_type& dim_,
	const filter_args& filter,
	const resource_flag_t nflags)
: detail::texture_base_type(
		r,
		filter,
		nflags),
  device(device),
  dim_(dim_),
  lock_dest(0)
{
	on_reset();
	if(data)
		set_data(data);
}

IDirect3DBaseTexture9* sge::d3d9::texture::do_reset()
{
	tex.reset(
		create_texture(
			device,
			dim(),
			filter(),
			flags(),
			false));
	return tex.get();
}

void sge::d3d9::texture::do_loss()
{
	tex.reset();
}

void sge::d3d9::texture::lock(const lock_flag_t lflags)
{
	lock(0, lflags);
}

void sge::d3d9::texture::lock(const lock_rect& r, const lock_flag_t lflags)
{
	lock(&r, lflags);
}

void sge::d3d9::texture::lock(const lock_rect* const r, const lock_flag_t lflags)
{
	if(flags() & resource_flags::dynamic)
		lock_dest = lock_texture(tex, r, lflags, flags());
	else
	{
		temp_tex.reset(
			create_texture(
				device,
				dim(),
				filter(),
				flags(),
				true));
		lock_dest = lock_texture(temp_tex, r, lflags, flags());
	}
}

void sge::d3d9::texture::unlock()
{
	if(flags() & resource_flags::dynamic)
		unlock_texture(tex);
	else
	{
		unlock_texture(temp_tex);
		update_texture(device, temp_tex.get(), tex.get());
		temp_tex.reset();
	}
	lock_dest = 0;
}

sge::texture::pointer sge::d3d9::texture::data()
{
	return lock_dest;
}

sge::texture::const_pointer sge::d3d9::texture::data() const
{
	return lock_dest;
}

void sge::d3d9::texture::set_data(const const_pointer data)
{
	const scoped_lock<texture*> l(make_scoped_lock(this, lock_flags::writeonly));
	copy_n(data, size(), lock_dest);
}

void sge::d3d9::texture::set_data(const const_pointer data, const lock_rect& r)
{
	//const scoped_lock<texture*> l(this, r);
	//std::copy(data, data + r.w() * r.h(), lock_dest);
}

const sge::texture::dim_type sge::d3d9::texture::dim() const
{
	return dim_;
}
