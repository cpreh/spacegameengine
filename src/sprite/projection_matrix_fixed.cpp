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


#include <sge/renderer/projection/dim.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_wh.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/projection_matrix_fixed.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::sprite::optional_matrix const
sge::sprite::projection_matrix_fixed(
	sge::sprite::projection_dim const _size
)
{
	return
		_size.get().content()
		!=
		0u
		?
			sge::sprite::optional_matrix(
				sge::renderer::projection::orthogonal_wh(
					fcppt::math::dim::structure_cast<
						sge::renderer::projection::dim,
						fcppt::cast::int_to_float_fun
					>(
						_size.get()
					),
					// TODO
					sge::renderer::projection::near{
						0.f
					},
					sge::renderer::projection::far{
						10.f
					}
				)
			)
		:
			sge::sprite::optional_matrix()
		;
}
