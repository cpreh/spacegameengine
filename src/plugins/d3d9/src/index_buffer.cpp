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


#include "../index_buffer.hpp"
#include "../d3dinclude.hpp"
#include "../convert/index_format.hpp"
#include "../convert/lock_mode.hpp"
#include "../convert/resource_flags.hpp"
#include "../convert/resource_flags_to_pool.hpp"
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <fcppt/text.hpp>

sge::d3d9::index_buffer::index_buffer(
	IDirect3DDevice9 *const _device,
	renderer::index::dynamic::format::type const _format,
	size_type const _size,
	renderer::resource_flags_field const &_resource_flags
)
:
	sge::renderer::index_buffer(),
	d3d9::resource(
		d3d9::convert::resource_flags_to_pool(
			_resource_flags
		)
	),
	device_(_device),
	buffer_(),
	resource_flags_(_resource_flags),
	format_(_format),
	size_(_size),
	stride_(
		sge::renderer::index::dynamic::format_stride(
			format_
		)
	),
	lock_dest_(0)
{
	this->init();
}

sge::d3d9::index_buffer::~index_buffer()
{
}

sge::d3d9::index_buffer::view_type const
sge::d3d9::index_buffer::lock(
	renderer::lock_mode::type const _mode,
	size_type const _first,
	size_type const _count
)
{
	return
		this->do_lock<
			index_buffer::view_type
		>(
			_first,
			_count,
			d3d9::convert::lock_mode(
				_mode,
				this->resource_flags()
			)
		);
}

sge::d3d9::index_buffer::const_view_type const
sge::d3d9::index_buffer::lock(
	size_type const _first,
	size_type const _count
) const
{
	return
		this->do_lock<
			index_buffer::const_view_type
		>(
			_first,
			_count,
			d3d9::lock_flags(
				D3DLOCK_READONLY
			)
		);
}

void
sge::d3d9::index_buffer::unlock() const
{
	if(
		!lock_dest_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d::index_buffer::unlock() you have to lock first!")
		);

	if(
		buffer_->Unlock()
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot unlock index buffer!")
		);

	lock_dest_ = 0;
}

sge::d3d9::index_buffer::size_type
sge::d3d9::index_buffer::size() const
{
	return size_;
}

sge::renderer::resource_flags_field const
sge::d3d9::index_buffer::resource_flags() const
{
	return resource_flags_;
}

sge::renderer::index::dynamic::format::type
sge::d3d9::index_buffer::format() const
{
	return format_;
}

IDirect3DIndexBuffer9 *
sge::d3d9::index_buffer::get() const
{
	return buffer_.get();
}

void
sge::d3d9::index_buffer::init()
{
	IDirect3DIndexBuffer9 *ret;

	if(
		device_->CreateIndexBuffer(
			static_cast<
				UINT
			>(
				size_
				*
				stride_
			),
			convert::resource_flags(
				this->resource_flags()
			).get(),
			convert::index_format(
				this->format()
			),
			this->pool(),
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateIndexBuffer() failed!")
		);

	buffer_.reset(
		ret
	);
}

void
sge::d3d9::index_buffer::on_loss()
{
	buffer_.reset();
}

void
sge::d3d9::index_buffer::on_reset()
{
	this->init();
}

template<
	typename View
>
View const
sge::d3d9::index_buffer::do_lock(
	size_type const _first,
	size_type const _count,
	d3d9::lock_flags const _flags
) const
{
	if(
		lock_dest_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d::index_buffer::lock() you have to unlock first!")
		);

	void *dest = 0;

	if(
		buffer_->Lock(
			static_cast<
				UINT
			>(
				_first
				*
				stride_
			),
			static_cast<
				UINT
			>(
				(
					_count == index_buffer::npos
					?
						this->size()
					:
						_count
				)
				*
				stride_
			),
			&dest,
			_flags.get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot lock index buffer!")
		);

	lock_dest_ =
		static_cast<
			sge::renderer::raw_pointer
		>(
			dest	
		);

	return
		View(
			lock_dest_,
			_count,
			format_
		);
}
