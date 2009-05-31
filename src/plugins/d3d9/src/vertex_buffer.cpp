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



#include "../vertex_buffer.hpp"
#include "../convert_to_pool.hpp"
#include "../convert_resource_flags.hpp"
#include "../convert_lock_flags.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::d3d9::vertex_buffer::vertex_buffer(
	d3d_device_ptr const device_,
	renderer::vf::dynamic_format const &format,
	size_type const sz,
	resource_flag_type const flags_)
:
	device_(device_),
	lock_dest(0),
	flags_(flags_),
	sz(sz),
	d3d_format(
		device_,
		format
	)
{
	init();
}

sge::d3d9::vertex_buffer::view_type const
sge::d3d9::vertex_buffer::lock(
	lock_flag_type const lflags,
	size_type const first,
	size_type const count)
{
	do_lock(
		convert_lock_flags(
			lflags,
			flags()
		),
		first,
		count
	);

	return view_type(
		lock_dest,
		count,
		format()
	);
}

sge::d3d9::vertex_buffer::const_view_type const
sge::d3d9::vertex_buffer::lock(
	size_type const offset,
	size_type const range) const
{
	do_lock(
		D3DLOCK_READONLY,
		offset,
		range
	);

	return const_view_type(
		lock_dest,
		count,
		format()
	);
}

void
sge::d3d9::vertex_buffer::unlock() const
{
	if(!lock_dest)
		throw exception(
			SGE_TEXT("d3d::vertex_buffer::unlock() you have to lock first!")
		);

/*#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(vertex_usage::diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = rgba_to_argb(it->diffuse());
#endif*/
	if(buffer->Unlock() != D3D_OK)
		throw exception(
			SGE_TEXT("Cannot unlock d3d vertex buffer!")
		);

	lock_dest = 0;
}

sge::d3d9::vertex_buffer::size_type
sge::d3d9::vertex_buffer::size() const
{
	return sz;
}

sge::d3d9::vertex_buffer::resource_flag_type
sge::d3d9::vertex_buffer::flags() const
{
	return flags_;
}

sge::renderer::vf::dynamic_format const &
sge::d3d9::vertex_buffer::format() const
{
	return d3d_format.format();
}

void
sge::d3d9::vertex_buffer::init()
{
	IDirect3DVertexBuffer9 *p;

	if(
		device_->CreateVertexBuffer(
			static_cast<UINT>(stride() * size()),
			convert_resource_flags(
				flags()
			),
			d3d_format.fvf(),
			convert_to_pool(
				flags()
			),
			&p,
			0
		) != D3D_OK
	)
		throw exception(
			SGE_TEXT("Cannot create vertex buffer!")
		);

	buffer.reset(p);
}

void sge::d3d9::vertex_buffer::on_loss()
{
	buffer.reset();
}

void sge::d3d9::vertex_buffer::on_reset()
{
	init();
}

void
sge::d3d9::vertex_buffer::do_lock(
	DWORD const lflags,
	size_type const offset,
	size_type const count) const
{
	if(lock_dest)
		throw exception(
			SGE_TEXT("d3d::vertex_buffer::lock() you have to unlock first!")
	);

	void *p = 0;

	if(
		buffer->Lock(
			static_cast<UINT>(offset * stride()),
			static_cast<UINT>(count * stride()),
			&p,
			lflags
		) != D3D_OK
	)
		throw exception(
			SGE_TEXT("Cannot lock d3d vertex buffer!")
		);

	lock_dest = static_cast<renderer::raw_pointer>(p);
/*#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(vertex_usage::diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = argb_to_rgba(it->diffuse());
#endif*/
}

sge::d3d9::vertex_buffer::size_type
sge::d3d9::vertex_buffer::stride() const
{
	return d3d_format.stride();
}
