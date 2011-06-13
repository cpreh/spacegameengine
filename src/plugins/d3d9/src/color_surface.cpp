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


#include "../color_surface.hpp"
#include "../d3dinclude.hpp"
#include "../devicefuncs/create_offscreen_plain_surface.hpp"
#include "../devicefuncs/get_render_target_data.hpp"
#include "../surfacefuncs/color_format.hpp"
#include "../surfacefuncs/dim.hpp"
#include "../surfacefuncs/is_render_target.hpp"
#include "../surfacefuncs/lock_rect.hpp"
#include "../surfacefuncs/unlock_rect.hpp"
#include "../make_pitch_2d.hpp"
#include "../optional_lock_rect.hpp"
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/move.hpp>
#include <fcppt/optional_impl.hpp>

sge::d3d9::color_surface::color_surface(
	IDirect3DDevice9 *const _device,
	d3d9::d3d_surface_unique_ptr _surface
)
:
	device_(_device),
	surface_(
		fcppt::move(
			_surface
		)
	),
	size_(
		surfacefuncs::dim(
			surface_.get()
		)
	),
	format_(
		surfacefuncs::color_format(
			surface_.get()
		)
	),
	is_render_target_(
		surfacefuncs::is_render_target(
			surface_.get()
		)
	)
{
}

sge::d3d9::color_surface::~color_surface()
{
}

sge::d3d9::color_surface::const_view const
sge::d3d9::color_surface::lock(
	rect const &_rect
) const
{
	if(
		is_render_target_
	)
	{
		temp_surface_.take(
			devicefuncs::create_offscreen_plain_surface(
				device_,
				size_,
				format_,
				D3DPOOL_SYSTEMMEM
			)
		);

		devicefuncs::get_render_target_data(
			device_,
			surface_.get(),
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
				format_,
				sge::d3d9::make_pitch_2d(
					locked_rect
				)
			)
		);
}

void
sge::d3d9::color_surface::unlock() const
{
	d3d9::surfacefuncs::unlock_rect(
		this->lock_surface()
	);

	if(
		is_render_target_
	)
		temp_surface_.reset();
}

sge::d3d9::color_surface::dim const
sge::d3d9::color_surface::size() const
{
	return
		surfacefuncs::dim(
			surface_.get()
		);
}

IDirect3DSurface9 *
sge::d3d9::color_surface::surface() const
{
	return surface_.get();
}

IDirect3DSurface9 *
sge::d3d9::color_surface::lock_surface() const
{
	return
		is_render_target_
		?
			temp_surface_.get()
		:
			surface_.get()
		;
}
