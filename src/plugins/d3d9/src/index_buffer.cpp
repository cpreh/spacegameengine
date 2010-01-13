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


#include "../index_buffer.hpp"
#include "../conversion.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::index_buffer::index_buffer(
	d3d_device_ptr const device_,
	renderer::index::format::type const format_,
	size_type const sz,
	resource_flag_type const flags_)
:
	resource(),
	device_(device_),
	buffer(),
	flags_(flags_),
	format_(format_),
	sz(sz),
	lock_dest(0)
{
	init();
}

sge::d3d9::index_buffer::view_type const
sge::d3d9::index_buffer::lock(
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
		format_
	);
}

void
sge::d3d9::index_buffer::lock(
	size_type const first,
	size_type const count) const
{
	do_lock(
		D3DLOCKMETHOD_READONLY,
		first,
		count
	);

	return const_view_type(
		lock_dest,
		count,
		format
	);
}

void sge::d3d9::index_buffer::unlock() const
{
	if(!lock_dest)
		throw exception(FCPPT_TEXT("d3d::index_buffer::unlock() you have to lock first!"));

	if(buffer->Unlock() != D3D_OK)
		throw exception(FCPPT_TEXT("Cannot unlock index buffer!"));

	lock_dest = 0;
}

sge::d3d9::index_buffer::size_type
sge::d3d9::index_buffer::size() const
{
	return sz;
}

sge::d3d9::index_buffer::resource_flag_type
sge::d3d9::index_buffer::flags() const
{
	return flags_;
}

void
sge::d3d9::index_buffer::init()
{
	IDirect3DIndexBuffer9 *p;
	if(
		device->CreateIndexBuffer(
			static_cast<UINT>(sz * stride()),
			convert_resource_flags(
				flags()
			),
			convert_index_format(
				format()
			),
			convert_to_pool(
				flags()
			),
			&p,
			0
		) != D3D_OK
	)
		throw exception(
			FCPPT_TEXT("Cannot create index buffer!")
		);

	buffer.reset(p);
}

void sge::d3d9::index_buffer::on_loss()
{
	buffer.reset();
}

void sge::d3d9::index_buffer::on_reset()
{
	init();
}

void sge::d3d9::index_buffer::do_lock(
	size_type const first,
	size_type const count,
	DWORD const lflags)
{
	if(lock_dest)
		throw exception(
			FCPPT_TEXT("d3d::index_buffer::lock() you have to unlock first!")
		);

	void *p = 0;

	if(
		buffer->Lock(
			static_cast<UINT>(first * stride()),
			static_cast<UINT>(count * stride()),
			&p,
			lflags
		) != D3D_OK
	)
		throw exception(
			FCPPT_TEXT("Cannot lock index buffer!")
		);

	lock_dest = static_cast<pointer>(p);
}
