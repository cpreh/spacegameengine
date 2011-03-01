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


#include "../planar.hpp"
#include "../basic_impl.hpp"
#include "../create_planar.hpp"
#include "../lock_planar.hpp"
#include "../optional_lock_rect.hpp"
#include "../unlock_planar.hpp"
#include "../update.hpp"
#include "../../convert/lock_mode.hpp"
#include "../../d3dinclude.hpp"
#include "../../lock_flags.hpp"
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>

sge::d3d9::texture::planar::planar(
	IDirect3DDevice9 *const _device,
	renderer::texture::planar_parameters const &_params
)
:
	texture::planar_basic(
		_device,
		_params
	),
	texture_(
		texture::create_planar(
			_device,
			_params,
			this->pool(),
			this->usage()
		)
	),
	temp_texture_(),
	lock_dest_()
{
}

sge::d3d9::texture::planar::~planar()
{
}

sge::d3d9::texture::planar::dim_type const
sge::d3d9::texture::planar::dim() const
{
	return this->parameters().dim();
}

sge::d3d9::texture::planar::view_type const
sge::d3d9::texture::planar::lock(
	renderer::lock_rect const &_rect,
	renderer::lock_mode::type const _mode
)
{
	return
		this->do_lock<
			planar::view_type
		>(
			&sge::image2d::view::make,
			_rect,
			d3d9::convert::lock_mode(
				_mode,
				this->resource_flags()
			)
		);
}

sge::d3d9::texture::planar::const_view_type const
sge::d3d9::texture::planar::lock(
	renderer::lock_rect const &_rect
) const
{
	return
		this->do_lock<
			planar::const_view_type
		>(
			&sge::image2d::view::make_const,
			_rect,
			d3d9::lock_flags(
				D3DLOCK_READONLY
			)
		);
}

void
sge::d3d9::texture::planar::unlock() const
{
	if(
		!this->needs_reset()
	)
		texture::unlock_planar(
			texture_.get(),
			renderer::stage_type(0u)
		);
	else
	{

		texture::unlock_planar(
			temp_texture_.get(),
			renderer::stage_type(0u)
		);

		texture::update(
			this->device(),
			temp_texture_.get(),
			texture_.get()
		);
	}

	lock_dest_.reset();
}

sge::renderer::color_surface_ptr const
sge::d3d9::texture::planar::surface(
	renderer::stage_type const _stage
)
{
}

sge::renderer::stage_type
sge::d3d9::texture::planar::stages() const
{
}

IDirect3DBaseTexture9 *
sge::d3d9::texture::planar::do_reset()
{
	texture_.take(
		texture::create_planar(
			this->device(),
			this->parameters(),
			this->pool(),
			this->usage()
		)
	);

	return texture_.get();
}

#if 0
void
sge::d3d9::texture::do_loss()
{
	texture_.reset();
}
#endif

template<
	typename View,
	typename MakeView
>
View const
sge::d3d9::texture::planar::do_lock(
	MakeView const &_make_view,
	renderer::lock_rect const &_rect,
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
		!this->needs_reset()
	)
		lock_dest_ =
			texture::lock_planar(
				texture_.get(),
				renderer::stage_type(
					0u
				),
				dest_rect,
				_flags
			);
	else
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
