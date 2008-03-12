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


#include "../../../algorithm_impl.hpp"
#include "../../../exception.hpp"
#include "../../../renderer/scoped_lock.hpp"
#include "../index_buffer.hpp"
#include "../conversion.hpp"

namespace
{
const sge::d3d9::index_buffer::size_type stride = sizeof(sge::d3d9::index_buffer::value_type);
}

sge::d3d9::index_buffer::index_buffer(renderer& r, const d3d_device_ptr device, const size_type sz, const resource_flag_t nflags, const const_pointer src)
: resource(r, nflags & resource_flags::dynamic),
  device(device),
  buffer(),
  _flags(nflags),
  sz(sz),
  lock_dest(0)
{
	init(src);
}

void sge::d3d9::index_buffer::init(const const_pointer src)
{
	const D3DFORMAT format = D3DFMT_INDEX32;
	const DWORD usage = convert_cast<DWORD>(flags());
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags());

	IDirect3DIndexBuffer9* p;
	if(device->CreateIndexBuffer(static_cast<UINT>(sz * stride), usage, format, pool, &p,0) != D3D_OK)
		throw exception(SGE_TEXT("Cannot create index buffer!"));
	buffer.reset(p);

	if(src)
	{
		const scoped_lock<index_buffer*> l(make_scoped_lock(this, lock_flags::writeonly));
		copy_n(src, size(), lock_dest);
	}
}

sge::d3d9::index_buffer::iterator sge::d3d9::index_buffer::begin()
{
	return iterator(lock_dest);
}

sge::d3d9::index_buffer::const_iterator sge::d3d9::index_buffer::begin() const
{
	return const_iterator(lock_dest);
}

sge::d3d9::index_buffer::iterator sge::d3d9::index_buffer::end()
{
	return iterator(lock_dest + size());
}

sge::d3d9::index_buffer::const_iterator sge::d3d9::index_buffer::end() const
{
	return const_iterator(lock_dest + size());
}

sge::d3d9::index_buffer::reverse_iterator sge::d3d9::index_buffer::rbegin()
{
	return reverse_iterator(end());
}

sge::d3d9::index_buffer::const_reverse_iterator sge::d3d9::index_buffer::rbegin() const
{
	return const_reverse_iterator(end());
}

sge::d3d9::index_buffer::reverse_iterator sge::d3d9::index_buffer::rend()
{
	return reverse_iterator(begin());
}

sge::d3d9::index_buffer::const_reverse_iterator sge::d3d9::index_buffer::rend() const
{
	return const_reverse_iterator(begin());
}

void sge::d3d9::index_buffer::lock(const lock_flag_t lflags, const size_type first, const size_type count)
{
	if(lock_dest)
		throw exception(SGE_TEXT("d3d::index_buffer::lock() you have to unlock first!"));
	void* p = 0;
	const DWORD d3dlflags = convert_lock_flags(lflags, flags());
	if(buffer->Lock(static_cast<UINT>(first * stride), static_cast<UINT>(count * stride), &p, d3dlflags) != D3D_OK)
		throw exception(SGE_TEXT("Cannot lock index buffer!"));
	lock_dest = static_cast<pointer>(p);
}

void sge::d3d9::index_buffer::lock(const lock_flag_t lflags)
{
	lock(lflags,0,size());
}

void sge::d3d9::index_buffer::unlock()
{
	if(!lock_dest)
		throw exception(SGE_TEXT("d3d::index_buffer::unlock() you have to lock first!"));
	if(buffer->Unlock() != D3D_OK)
		throw exception(SGE_TEXT("Cannot unlock index buffer!"));
	lock_dest = 0;
}

sge::d3d9::index_buffer::size_type sge::d3d9::index_buffer::size() const
{
	return sz;
}

sge::resource_flag_t sge::d3d9::index_buffer::flags() const
{
	return _flags;
}

void sge::d3d9::index_buffer::resize(const size_type newsize, const const_pointer new_data)
{
	if(lock_dest)
		throw exception(SGE_TEXT("d3d::index_buffer::resize() you have to unlock before resizing!"));

	sz = newsize;
	init(new_data);
}

void sge::d3d9::index_buffer::set_data(const const_pointer src, const size_type first, const size_type count)
{
	const scoped_lock<index_buffer*> lock_(make_scoped_lock(this, first, count, lock_flags::writeonly));
	copy_n(src + first, count, data());
}

void sge::d3d9::index_buffer::on_loss()
{
	buffer.reset();
}

void sge::d3d9::index_buffer::on_reset()
{
	init();
}

sge::d3d9::index_buffer::pointer sge::d3d9::index_buffer::data()
{
	return lock_dest;
}

sge::d3d9::index_buffer::const_pointer sge::d3d9::index_buffer::data() const
{
	return lock_dest;
}

sge::d3d9::index_buffer::reference sge::d3d9::index_buffer::operator[](const size_type sz)
{
	return *(data() + sz);
}

sge::d3d9::index_buffer::const_reference sge::d3d9::index_buffer::operator[](const size_type sz) const
{
	return *(data() + sz);
}
