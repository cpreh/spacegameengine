/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/convert/index_format.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/d3d9/convert/resource_flags.hpp>
#include <sge/d3d9/convert/resource_flags_to_pool.hpp>
#include <sge/renderer/dim1.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>


sge::d3d9::index_buffer::index_buffer(
	IDirect3DDevice9 &_device,
	sge::renderer::index::buffer_parameters const &_parameters
)
:
	sge::renderer::index::buffer(),
	sge::d3d9::resource(
		sge::d3d9::convert::resource_flags_to_pool(
			_parameters.flags()
		)
	),
	device_(
		_device
	),
	buffer_(),
	resource_flags_(
		_parameters.flags()
	),
	format_(
		_parameters.format()
	),
	size_(
		_parameters.count()
	),
	stride_(
		sge::renderer::index::dynamic::format_stride(
			format_
		)
	),
	lock_dest_(
		nullptr
	)
{
	this->init();
}

sge::d3d9::index_buffer::~index_buffer()
{
}

sge::renderer::index::dynamic::view
sge::d3d9::index_buffer::lock(
	sge::renderer::lock_segment const &_segment,
	sge::renderer::lock_mode const _mode
)
{
	return
		this->do_lock<
			sge::renderer::index::dynamic::view
		>(
			_segment,
			sge::renderer::lock_flags::from_mode(
				_mode
			)
		);
}

sge::renderer::index::dynamic::const_view
sge::d3d9::index_buffer::lock_c(
	sge::renderer::lock_segment const &_segment
) const
{
	return
		this->do_lock<
			sge::renderer::index::dynamic::const_view
		>(
			_segment,
			sge::renderer::lock_flags::method::read
		);
}

void
sge::d3d9::index_buffer::unlock() const
{
	if(
		lock_dest_
		==
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d::index_buffer::unlock() you have to lock first!")
		);


	// TODO: Move this to another function
	if(
		this->get().Unlock()
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot unlock index buffer!")
		);

	lock_dest_ =
		nullptr;
}

sge::renderer::dim1
sge::d3d9::index_buffer::size() const
{
	return
		sge::renderer::dim1{
			size_.get()
		};
}

sge::renderer::resource_flags_field
sge::d3d9::index_buffer::resource_flags() const
{
	return
		resource_flags_;
}

sge::renderer::index::dynamic::format
sge::d3d9::index_buffer::format() const
{
	return
		format_;
}

IDirect3DIndexBuffer9 &
sge::d3d9::index_buffer::get() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			buffer_
		);
}

void
sge::d3d9::index_buffer::init()
{
	// TODO: Move this to another function
	IDirect3DIndexBuffer9 *ret;

	if(
		device_.CreateIndexBuffer(
			static_cast<
				UINT
			>(
				size_.get()
				*
				stride_
			),
			sge::d3d9::convert::resource_flags(
				this->resource_flags()
			).get(),
			sge::d3d9::convert::index_format(
				this->format()
			),
			this->pool(),
			&ret,
			nullptr
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateIndexBuffer() failed!")
		);

	buffer_ =
		sge::d3d9::index_buffer::optional_d3d_index_buffer_unique_ptr(
			sge::d3d9::index_buffer::d3d_index_buffer_unique_ptr(
				ret
			)
		);
}

void
sge::d3d9::index_buffer::on_loss()
{
	buffer_ =
		sge::d3d9::index_buffer::optional_d3d_index_buffer_unique_ptr();
}

void
sge::d3d9::index_buffer::on_reset()
{
	this->init();
}

template<
	typename View
>
View
sge::d3d9::index_buffer::do_lock(
	sge::renderer::lock_segment const &_segment,
	sge::renderer::lock_flags::method const _method
) const
{
	if(
		lock_dest_
		!=
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d::index_buffer::lock() you have to unlock first!")
		);

	// TODO: Move this to another function
	void *dest(
		nullptr
	);

	if(
		this->get().Lock(
			fcppt::cast::size<
				UINT
			>(
				_segment.pos().x()
				*
				stride_
			),
			fcppt::cast::size<
				UINT
			>(
				_segment.size().w()
				*
				stride_
			),
			&dest,
			sge::d3d9::convert::lock_flags(
				_method,
				this->resource_flags()
			).get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Cannot lock index buffer!")
		);

	lock_dest_ =
		fcppt::cast::from_void_ptr<
			sge::renderer::raw_pointer
		>(
			dest
		);

	return
		View(
			lock_dest_,
			_segment.size().w(),
			format_
		);
}
