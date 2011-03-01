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


#include "../vertex_buffer.hpp"
#include "../d3dinclude.hpp"
#include "../convert/lock_mode.hpp"
#include "../convert/resource_flags_to_pool.hpp"
#include "../convert/resource_flags.hpp"
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::vertex_buffer::vertex_buffer(
	IDirect3DDevice9 *const _device,
	renderer::vf::dynamic::part const &_format_part,
	renderer::vf::dynamic::part_index const _format_part_index,
	size_type const _size,
	renderer::resource_flags_field const &_resource_flags
)
:
	sge::renderer::vertex_buffer(),
	d3d9::resource(
		convert::resource_flags_to_pool(
			_resource_flags
		)
	),
	device_(_device),
	format_part_(_format_part),
	format_part_index_(_format_part_index),
	size_(_size),
	resource_flags_(_resource_flags),
	buffer_(),
	lock_dest_(0)
{
	this->init();
}

sge::d3d9::vertex_buffer::view_type const
sge::d3d9::vertex_buffer::lock(
	renderer::lock_mode::type const _lock_mode,
	size_type const _first,
	size_type const _count
)
{
	return
		this->do_lock<
			view_type
		>(
			_first,
			_count,
			convert::lock_mode(
				_lock_mode,
				this->resource_flags()
			)
		);
}

sge::d3d9::vertex_buffer::const_view_type const
sge::d3d9::vertex_buffer::lock(
	size_type const _first,
	size_type const _count
) const
{
	return
		this->do_lock<
			const_view_type
		>(
			_first,
			_count,
			d3d9::lock_flags(
				D3DLOCK_READONLY
			)
		);
}

void
sge::d3d9::vertex_buffer::unlock() const
{
	if(
		!lock_dest_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d9::vertex_buffer::unlock() you have to lock first!")
		);

// FIXME!
/*#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(vertex_usage::diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = rgba_to_argb(it->diffuse());
#endif*/
	if(
		buffer_->Unlock()
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot unlock d3d vertex buffer!")
		);

	lock_dest_ = 0;
}

sge::d3d9::vertex_buffer::size_type
sge::d3d9::vertex_buffer::size() const
{
	return size_;
}

sge::renderer::resource_flags_field const
sge::d3d9::vertex_buffer::resource_flags() const
{
	return resource_flags_;
}

sge::renderer::vf::dynamic::part const
sge::d3d9::vertex_buffer::format_part() const
{
	return format_part_;
}

sge::renderer::vf::dynamic::part_index const
sge::d3d9::vertex_buffer::format_part_index() const
{
	return format_part_index_;
}

void
sge::d3d9::vertex_buffer::init()
{
	IDirect3DVertexBuffer9 *ret;

	if(
		device_->CreateVertexBuffer(
			static_cast<
				UINT
			>(
				this->stride()
				* this->size()
			),
			convert::resource_flags(
				this->resource_flags()
			).get(),
			0, // no FVF
			this->pool(),
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot create vertex buffer!")
		);

	buffer_.reset(
		ret
	);
}

void
sge::d3d9::vertex_buffer::on_loss()
{
	buffer_.reset();
}

void
sge::d3d9::vertex_buffer::on_reset()
{
	this->init();
}

template<
	typename View
>
View const
sge::d3d9::vertex_buffer::do_lock(
	size_type const _first,
	size_type const _count,
	d3d9::lock_flags const _lock_flags
) const
{
	if(
		lock_dest_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d::vertex_buffer::lock() you have to unlock first!")
		);

	void *data = 0;

	if(
		buffer_->Lock(
			static_cast<
				UINT
			>(
				_first
				* this->stride()
			),
			static_cast<
				UINT
			>(
				_count
				* this->stride()
			),
			&data,
			_lock_flags.get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot lock d3d vertex buffer!")
		);

	lock_dest_ =
		static_cast<
			renderer::raw_pointer
		>(
			data
		);
// FIXME!
/*#ifndef SGE_USE_ARGB
	if(get_vertex_format().uses(vertex_usage::diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = argb_to_rgba(it->diffuse());
#endif*/
	return
		View(
			lock_dest_,
			_count,
			this->format_part(),
			this->format_part_index()
		);
}

sge::d3d9::vertex_buffer::size_type
sge::d3d9::vertex_buffer::stride() const
{
	return format_part_.stride();
}
