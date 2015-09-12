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
#include <sge/d3d9/make_pitch_2d.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/devicefuncs/create_offscreen_plain_surface.hpp>
#include <sge/d3d9/devicefuncs/get_render_target_data.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/color_create.hpp>
#include <sge/d3d9/surface/color_create_unique_ptr.hpp>
#include <sge/d3d9/surface/color_holder.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/unlock_rect.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_assign.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/box/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::d3d9::surface::color::color(
	IDirect3DDevice9 &_device,
	sge::image::color::format const _format,
	sge::d3d9::surface::color_create_unique_ptr &&_create
)
:
	sge::d3d9::resource(
		sge::d3d9::needs_reset::yes
	),
	device_(
		_device
	),
	create_(
		std::move(
			_create
		)
	),
	format_(
		_format
	),
	color_holder_(),
	temp_surface_()
{
	this->init();
}

sge::d3d9::surface::color::~color()
{
}

sge::d3d9::surface::color::view const
sge::d3d9::surface::color::lock(
	lock_area const &,
	sge::renderer::lock_mode
)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Locking color surfaces that are not texture surfaces is not supported!")
	);
}

sge::d3d9::surface::color::const_view const
sge::d3d9::surface::color::lock(
	lock_area const &_rect
) const
{
	sge::d3d9::surface::color_holder const &holder(
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			color_holder_
		)
	);

	if(
		holder.is_render_target()
	)
	{
		sge::d3d9::surface::d3d_unique_ptr const &temp_surface(
			fcppt::optional_assign(
				temp_surface_,
				sge::d3d9::devicefuncs::create_offscreen_plain_surface(
					device_,
					holder.size(),
					format_,
					D3DPOOL_SYSTEMMEM
				)
			)
		);

		sge::d3d9::devicefuncs::get_render_target_data(
			device_,
			this->surface(),
			*temp_surface
		);
	}

	D3DLOCKED_RECT const locked_rect(
		sge::d3d9::surfacefuncs::lock_rect(
			this->lock_surface(),
			this->area()
			==
			_rect
			?
				sge::d3d9::optional_lock_rect()
			:
				sge::d3d9::optional_lock_rect(
					_rect
				)
			,
			fcppt::strong_typedef_construct_cast<
				sge::d3d9::lock_flags,
				fcppt::cast::size_fun
			>(
				fcppt::cast::to_unsigned(
					D3DLOCK_READONLY
				)
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
					locked_rect,
					_rect.size(),
					format_
				)
			)
		);
}

void
sge::d3d9::surface::color::unlock() const
{
	sge::d3d9::surfacefuncs::unlock_rect(
		this->lock_surface()
	);

	if(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			color_holder_
		)->is_render_target()
	)
		temp_surface_ =
			sge::d3d9::surface::optional_d3d_unique_ptr();
}

sge::d3d9::surface::color::dim const
sge::d3d9::surface::color::size() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			color_holder_
		)->size();
}

sge::d3d9::surface::color::color_format
sge::d3d9::surface::color::format() const
{
	return
		format_;
}

IDirect3DSurface9 &
sge::d3d9::surface::color::surface() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			color_holder_
		)->get();
}

IDirect3DSurface9 &
sge::d3d9::surface::color::lock_surface() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			color_holder_
		)->is_render_target()
		?
			*FCPPT_ASSERT_OPTIONAL_ERROR(
				temp_surface_
			)
		:
			this->surface()
		;
}

void
sge::d3d9::surface::color::init()
{
	color_holder_ =
		optional_color_holder_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::surface::color_holder
			>(
				create_->create()
			)
		);
}

void
sge::d3d9::surface::color::on_loss()
{
	temp_surface_ =
		sge::d3d9::surface::optional_d3d_unique_ptr();

	color_holder_ =
		optional_color_holder_unique_ptr();
}

void
sge::d3d9::surface::color::on_reset()
{
	this->init();
}
