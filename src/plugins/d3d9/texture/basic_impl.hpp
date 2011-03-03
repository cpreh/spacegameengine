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


#ifndef SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include "basic.hpp"
#include "pool.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>

template<
	typename Types
>
sge::d3d9::texture::basic<Types>::basic(
	IDirect3DDevice9 *const _device,
	parameters_type const &_parameters
)
:
	Types::base(),
	d3d9::texture::base(0),
	d3d9::resource(
		texture::pool(
			_parameters.resource_flags(),
			_parameters.capabilities()
		)
	),
	device_(_device),
	parameters_(_parameters),
	main_texture_(
		Types::create()(
			_device,
			_parameters
		)
	),
	temp_texture_(),
	lock_dest_()
{
}

template<
	typename Types
>
sge::d3d9::texture::basic<Types>::~basic()
{
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::parameters_type const &
sge::d3d9::texture::basic<Types>::parameters() const
{
	return parameters_;
}

template<
	typename Types
>
IDirect3DDevice9 *
sge::d3d9::texture::basic<Types>::device() const
{
	return device_;
}

template<
	typename Types
>
sge::renderer::resource_flags_field const
sge::d3d9::texture::basic<Types>::resource_flags() const
{
	return this->parameters().resource_flags();
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::view_type const
sge::d3d9::texture::basic<Types>::lock_impl(
	lock_function const &_lock,
	lock_area const &_area,
	renderer::lock_mode::type const _mode
)
{
	return
		this->do_lock<
			view_type
		>(
			make_view,
			_area,
			d3d9::convert::lock_mode(
				_mode,
				this->resource_flags()
			)
		);
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::const_view_type const
sge::d3d9::texture::basic<Types>::lock_impl(
	lock_function const &_lock,
	lock_area const &_area
)
{
	return
		this->do_lock<
			planar::const_view_type
		>(
			make_const_view,
			_area,
			d3d9::lock_flags(
				D3DLOCK_READONLY
			)
		);
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::unlock_impl(
	unlock_function const &_unlock
) const
{
	if(
		this->needs_reset()
	)
	{
		_unlock(
			temp_texture_.get(),
			renderer::stage_type(0u)
		);

		texture::update(
			this->device(),
			temp_texture_.get(),
			main_texture_.get()
		);
	}
		_unlock(
			main_texture_.get(),
			renderer::stage_type(0u)
		);
	
	lock_dest_.reset();
}

template<
	typename Types
>
template<
	typename View,
	typename MakeView
>
View const
sge::d3d9::texture::basic<Types>::do_lock(
	MakeView const &_make_view,
	lock_area const &_area,
	d3d9::lock_flags const _flags
) const
{
	texture::optional_lock_rect const dest_rect(
		_rect
		== this->rect()
		?
			texture::optional_lock_rect()
		:
			texture::optional_lock_rect(
				_rect
			)
	);

	if(
		this->needs_reset()
	)
	{
		temp_texture_.take(
			texture::create_planar(
				this->device(),
				this->parameters(),
				D3DPOOL_SYSTEMMEM,
				d3d9::usage(
					0u
				)
			)
		);

		lock_dest_ =
			texture::lock_planar(
				temp_texture_.get(),
				renderer::stage_type(
					0u
				),
				dest_rect,
				_flags
			);
	}	
	else
		lock_dest_ =
			texture::lock_planar(
				texture_.get(),
				renderer::stage_type(
					0u
				),
				dest_rect,
				_flags
			);
	

	return
		View(
			_make_view(
				static_cast<
					sge::renderer::raw_pointer
				>(
					lock_dest_->pBits
				),
				_rect.size(),
				this->parameters().color_format(),
				sge::image2d::view::optional_pitch(
					// TODO!
				)
			)
		);

}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_reset()
{
	main_texture_.reset();
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_loss()
{
	this->init();
}


#endif
