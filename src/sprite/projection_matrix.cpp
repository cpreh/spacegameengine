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


#include <sge/sprite/projection_matrix.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>

sge::sprite::matrix const
sge::sprite::projection_matrix(
	sge::renderer::viewport const &_viewport
)
{
	return
		fcppt::math::matrix::orthogonal<
			sge::sprite::matrix::value_type
		>(
			static_cast<
				sge::sprite::matrix::value_type
			>(
				0
			),
			static_cast<
				sge::sprite::matrix::value_type
			>(
				_viewport.get().dimension().w()
			),
			static_cast<
				sge::sprite::matrix::value_type
			>(
				_viewport.get().dimension().h()
			),
			static_cast<
				sge::sprite::matrix::value_type
			>(
				0
			),
			static_cast<
				sge::sprite::matrix::value_type
			>(
				0
			),
			static_cast<
				sge::sprite::matrix::value_type
			>(
				10
			)
		);
}
