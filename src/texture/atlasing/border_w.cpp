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


#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/pos.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_w.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <fcppt/math/vector/null.hpp>


void
sge::texture::atlasing::border_w(
	sge::renderer::texture::planar &_texture,
	sge::image2d::view::const_object const &_source,
	sge::texture::atlasing::inner_rect const &_inner_area,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::renderer::dim2 const dim(
		sge::image2d::view::size(
			_source
		)
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				fcppt::math::vector::null<
					sge::renderer::lock_rect::vector
				>(),
				sge::renderer::lock_rect::dim(
					1u,
					dim.h()
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().left() - 1u,
			_inner_area.get().top()
		),
		_uninitialized
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector(
					dim.w() - 1u,
					0u
				),
				sge::renderer::lock_rect::dim(
					1u,
					dim.h()
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().right() + 1u,
			_inner_area.get().top()
		),
		_uninitialized
	);
}
