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


#include "../../../exception.hpp"
#include "../../../renderer/lock_ptr.hpp"
#include "../vertex_buffer.hpp"
#include "../vertex_format.hpp"
#include "../conversion.hpp"

sge::d3d::vertex_buffer::vertex_buffer(renderer* const r, const d3d_device_ptr device, const sge::vertex_format& format, const size_type sz, const resource_flag_t nflags, const const_pointer src)
: resource(r, nflags & RF_Dynamic),
  device(device), lock_dest(0), _flags(nflags), sz(sz), format(format), d3d_format(device,format)
{
	init(src);
}

void sge::d3d::vertex_buffer::init(const const_pointer src)
{
	const DWORD fvf = d3d_format.fvf();
	const DWORD usage = convert_cast<DWORD>(flags());
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags());

	IDirect3DVertexBuffer9* p;
	if(device->CreateVertexBuffer(static_cast<UINT>(stride() * size()),usage,fvf,pool,&p,0) != D3D_OK)
		throw exception("Cannot create vertex buffer!");
	buffer.reset(p);
	if(src)
	{
		lock_ptr<vertex_buffer*> l(this);
		copy(src,src+sz*stride(),lock_dest);
	}
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::begin()
{
	return create_iterator(lock_dest);
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::begin() const
{
	return create_iterator(const_pointer(lock_dest));
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::end()
{
	return create_iterator(lock_dest + size());
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::end() const
{
	return create_iterator(const_pointer(lock_dest + size()));
}

sge::d3d::vertex_buffer::reverse_iterator sge::d3d::vertex_buffer::rbegin()
{
	return reverse_iterator(end());
}

sge::d3d::vertex_buffer::const_reverse_iterator sge::d3d::vertex_buffer::rbegin() const
{
	return const_reverse_iterator(end());
}

sge::d3d::vertex_buffer::reverse_iterator sge::d3d::vertex_buffer::rend()
{
	return reverse_iterator(begin());
}

sge::d3d::vertex_buffer::const_reverse_iterator sge::d3d::vertex_buffer::rend() const
{
	return const_reverse_iterator(begin());
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::create_iterator(const pointer data)
{
	return iterator(data,d3d_format.stride(),d3d_format.get_offset_info());
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::create_iterator(const const_pointer data) const
{
	return const_iterator(data,d3d_format.stride(),d3d_format.get_offset_info());
}

void sge::d3d::vertex_buffer::lock(const lock_flag_t lflags, const size_type first, const size_type count)
{
	if(lock_dest)
		throw std::logic_error("d3d::vertex_buffer::lock() you have to unlock first!");
	void* p = 0;
	const DWORD d3dlflags = convert_lock_flags(flags(),lflags);
	if(buffer->Lock(static_cast<UINT>(first * stride()), static_cast<UINT>(count * stride()), &p, d3dlflags) != D3D_OK)
		throw exception("Cannot lock d3d vertex buffer!");
	lock_dest = static_cast<pointer>(p);
#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(VU_Diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = argb_to_rgba(it->diffuse());
#endif
}

void sge::d3d::vertex_buffer::lock(const lock_flag_t lflags)
{
	lock(lflags,0,size());
}

void sge::d3d::vertex_buffer::set_data(const const_pointer src, const size_type first, const size_type count)
{
	lock_ptr<vertex_buffer*> _l(this, lock_flags::discard, first, count);
	copy(src + first*stride(), src + (first+count)*stride(), data());
}

void sge::d3d::vertex_buffer::unlock()
{
	if(!lock_dest)
		throw exception("d3d::vertex_buffer::unlock() you have to lock first!");

#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(VU_Diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = rgba_to_argb(it->diffuse());
#endif
	if(buffer->Unlock() != D3D_OK)
		throw exception("Cannot unlock d3d vertex buffer!");
	lock_dest = 0;
}

void sge::d3d::vertex_buffer::resize(const size_type newsize, const const_pointer new_data)
{
	if(lock_dest)
		throw exception("d3d::vertex_buffer::resize() you have to unlock before resizing!");

	sz = newsize;
	init(new_data);
}

void sge::d3d::vertex_buffer::on_loss()
{
	buffer.reset();
}

void sge::d3d::vertex_buffer::on_reset()
{
	init();
}

sge::d3d::vertex_buffer::size_type sge::d3d::vertex_buffer::size() const
{
	return sz;
}

sge::vertex_size sge::d3d::vertex_buffer::stride() const
{
	return d3d_format.stride();
}

sge::resource_flag_t sge::d3d::vertex_buffer::flags() const
{
	return _flags;
}

sge::d3d::vertex_buffer::pointer sge::d3d::vertex_buffer::data()
{
	return lock_dest;
}

sge::d3d::vertex_buffer::const_pointer sge::d3d::vertex_buffer::data() const
{
	return lock_dest;
}

const sge::vertex_format& sge::d3d::vertex_buffer::get_vertex_format() const
{
	return format;
}

sge::vertex_buffer::reference sge::d3d::vertex_buffer::operator[](const size_type sz)
{
	return *(begin() + sz);
}

sge::vertex_buffer::const_reference sge::d3d::vertex_buffer::operator[](const size_type sz) const
{
	return *(begin() + sz);
}
