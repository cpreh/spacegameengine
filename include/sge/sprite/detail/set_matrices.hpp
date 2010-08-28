/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_SET_MATRICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_MATRICES_HPP_INCLUDED

#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/transform_matrix.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix_mode.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename TypeChoices
>
void
set_matrices(
	renderer::device_ptr const _device
)
{
	_device->transform(
		sge::renderer::matrix_mode::world,
		sprite::transform_matrix<
			TypeChoices
		>(
			_device->screen_size()
		)
	);

	_device->transform(
		sge::renderer::matrix_mode::projection,
		sprite::projection_matrix<
			TypeChoices
		>()
	);
}

}
}
}

#endif
