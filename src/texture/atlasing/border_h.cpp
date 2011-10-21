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


#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/texture/pos_type.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


void
sge::texture::atlasing::border_h(
	renderer::texture::planar &_texture,
	image2d::view::const_object const &_source,
	renderer::lock_rect const &_outer_area,
	renderer::lock_rect const &_inner_area
)
{
	renderer::dim2 const dim(
		image2d::view::size(
			_source
		)
	);

	texture::sub_data(
		_texture,
		image2d::view::sub(
			_source,
			renderer::lock_rect(
				renderer::lock_rect::vector::null(),
				renderer::lock_rect::dim(
					dim.w(),
					1u
				)
			)
		),
		texture::pos_type(
			_inner_area.left(),
			_outer_area.top()
		)
	);

	if(
		_inner_area.bottom() + 1u
		== _outer_area.bottom()
	)
		return;

	texture::sub_data(
		_texture,
		image2d::view::sub(
			_source,
			renderer::lock_rect(
				renderer::lock_rect::vector(
					0,
					dim.h() - 1u
				),
				renderer::lock_rect::dim(
					dim.w(),
					1u
				)
			)
		),
		texture::pos_type(
			_inner_area.left(),
			_outer_area.bottom() - 1u
		)
	);
}
