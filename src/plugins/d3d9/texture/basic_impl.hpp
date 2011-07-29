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
#include "update.hpp"
#include "usage.hpp"
#include "../d3dinclude.hpp"
#include "../lock_flags.hpp"
#include "../make_pitch.hpp"
#include "../convert/color_format.hpp"
#include "../convert/lock_flags.hpp"
#include "../convert/to_color_format.hpp"
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/optional_impl.hpp>

template<
	typename Types
>
sge::d3d9::texture::basic<Types>::basic(
	IDirect3DDevice9 *const _device,
	parameters_type const &_parameters
)
:
	Types::base(),
	d3d9::texture::base(),
	d3d9::resource(
		texture::pool(
			_parameters.resource_flags(),
			_parameters.capabilities()
		)
	),
	device_(_device),
	parameters_(_parameters),
	d3d_color_format_(
		d3d9::convert::color_format(
			_parameters.color_format()
		)
	),
	color_format_(
		d3d9::convert::to_color_format(
			d3d_color_format_
		)
	),
	usage_(
		texture::usage(
			_parameters.resource_flags(),
			_parameters.capabilities()
		)
	),
	main_texture_(),
	temp_texture_(),
	locked_dest_()
{
	this->init();
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
sge::renderer::resource_flags_field const
sge::d3d9::texture::basic<Types>::resource_flags() const
{
	return this->parameters().resource_flags();
}

template<
	typename Types
>
sge::renderer::texture::capabilities_field const
sge::d3d9::texture::basic<Types>::capabilities() const
{
	return this->parameters().capabilities();
}

template<
	typename Types
>
sge::renderer::texture::mipmap::object const
sge::d3d9::texture::basic<Types>::mipmap() const
{
	return this->parameters().mipmap();
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::d3d_type *
sge::d3d9::texture::basic<Types>::get() const
{
	return main_texture_.get();
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
typename sge::d3d9::texture::basic<Types>::view const
sge::d3d9::texture::basic<Types>::lock_impl(
	lock_function const &_lock,
	lock_area const &_area,
	renderer::lock_mode::type const _mode
)
{
	return
		this->do_lock<
			view
		>(
			sge::image::view::make<
				image_tag
			>,
			_lock,
			_area,
			renderer::lock_flags::from_mode(
				_mode
			)
		);
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::const_view const
sge::d3d9::texture::basic<Types>::lock_impl(
	lock_function const &_lock,
	lock_area const &_area
) const
{
	return
		this->do_lock<
			const_view
		>(
			sge::image::view::make_const<
				image_tag
			>,
			_lock,
			_area,
			renderer::lock_flags::method::read
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
			renderer::stage(
				0u
			)
		);

		texture::update(
			device_,
			temp_texture_.get(),
			main_texture_.get()
		);
	}
		_unlock(
			main_texture_.get(),
			renderer::stage(
				0u
			)
		);
	
	locked_dest_.reset();
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
	lock_function const &_lock,
	lock_area const &_area,
	renderer::lock_flags::method::type const _method
) const
{
	typedef typename Types::lock_dest lock_dest;

	lock_dest const dest_rect(
		_area
		== this->area()
		?
			lock_dest()
		:
			lock_dest(
				_area
			)
	);

	d3d9::lock_flags const lock_method(
		d3d9::convert::lock_flags(
			_method,
			this->resource_flags()
		)
	);

	if(
		this->needs_reset()
	)
	{
		temp_texture_.take(
			this->create(
				D3DPOOL_SYSTEMMEM,
				d3d9::usage(
					0u
				)
			)
		);

		locked_dest_ =
			_lock(
				temp_texture_.get(),
				renderer::stage(
					0u
				),
				dest_rect,
				lock_method
			);
	}
	else
		locked_dest_ =
			_lock(
				main_texture_.get(),
				renderer::stage(
					0u
				),
				dest_rect,
				lock_method
			);
	

	return
		View(
			_make_view(
				static_cast<
					sge::renderer::raw_pointer
				>(
					locked_dest_->pBits
				),
				_area.size(),
				color_format_,
				d3d9::make_pitch(
					*locked_dest_
				)
			)
		);
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::d3d_unique_ptr
sge::d3d9::texture::basic<Types>::create(
	D3DPOOL const _pool,
	d3d9::usage const _usage
) const
{
	return
		Types::create()(
			device_,
			this->parameters(),
			d3d_color_format_,
			_pool,
			_usage
		);
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::init()
{
	main_texture_.take(
		this->create(
			this->pool(),
			usage_
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
