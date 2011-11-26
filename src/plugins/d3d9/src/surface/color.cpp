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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/make_pitch_2d.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/devicefuncs/create_offscreen_plain_surface.hpp>
#include <sge/d3d9/devicefuncs/get_render_target_data.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/color_create.hpp>
#include <sge/d3d9/surface/color_holder.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/unlock_rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::d3d9::surface::color::color(
	IDirect3DDevice9 *const _device,
	surface::color_create_unique_ptr _create
)
:
	resource(
		d3d9::needs_reset::yes
	),
	device_(
		_device
	),
	create_(
		fcppt::move(
			_create
		)
	),
	color_holder_(),
	temp_surface_()
{
	this->init();
}

sge::d3d9::surface::color::~color()
{
}

sge::d3d9::surface::color::const_view const
sge::d3d9::surface::color::lock(
	rect const &_rect
) const
{
	if(
		color_holder_->is_render_target()
	)
	{
		temp_surface_.take(
			devicefuncs::create_offscreen_plain_surface(
				device_,
				color_holder_->size(),
				color_holder_->format(),
				D3DPOOL_SYSTEMMEM
			)
		);

		devicefuncs::get_render_target_data(
			device_,
			this->surface(),
			temp_surface_.get()
		);
	}

	D3DLOCKED_RECT const locked_rect(
		d3d9::surfacefuncs::lock_rect(
			this->lock_surface(),
			this->area() == _rect
			?
				d3d9::optional_lock_rect()
			:
				d3d9::optional_lock_rect(
					_rect
				)
			,
			d3d9::lock_flags(
				D3DLOCK_READONLY
			)
		)
	);

	return
		const_view(
			sge::image2d::view::make_const(
				static_cast<
					sge::renderer::const_raw_pointer
				>(
					locked_rect.pBits
				),
				_rect.size(),
				color_holder_->format(),
				sge::d3d9::make_pitch_2d(
					locked_rect,
					_rect.size(),
					color_holder_->format()
				)
			)
		);
}

void
sge::d3d9::surface::color::unlock() const
{
	d3d9::surfacefuncs::unlock_rect(
		this->lock_surface()
	);

	if(
		color_holder_->is_render_target()
	)
		temp_surface_.reset();
}

sge::d3d9::surface::color::dim const
sge::d3d9::surface::color::size() const
{
	return color_holder_->size();
}

IDirect3DSurface9 *
sge::d3d9::surface::color::surface() const
{
	return color_holder_->get();
}

IDirect3DSurface9 *
sge::d3d9::surface::color::lock_surface() const
{
	return
		color_holder_->is_render_target()
		?
			temp_surface_.get()
		:
			this->surface()
		;
}

void
sge::d3d9::surface::color::init()
{
	color_holder_.take(
		fcppt::make_unique_ptr<
			surface::color_holder
		>(
			create_->create()
		)
	);
}

void
sge::d3d9::surface::color::on_loss()
{
	temp_surface_.reset();

	color_holder_.reset();
}

void
sge::d3d9::surface::color::on_reset()
{
	this->init();
}
