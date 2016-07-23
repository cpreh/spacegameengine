/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/projection/check_near.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/dim.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/perspective_wh.hpp>
#include <fcppt/math/matrix/row.hpp>


sge::renderer::matrix4
sge::renderer::projection::perspective_wh(
	sge::renderer::projection::dim const &_dim,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	sge::renderer::impl::projection::check_near_far(
		_near,
		_far
	);

	sge::renderer::impl::projection::check_near(
		_near
	);

	sge::renderer::scalar const
		far(
			_far.get()
		),
		near(
			_near.get()
		),
		h(
			_dim.h()
		),
		w(
			_dim.w()
		),
		zero(
			0.f
		),
		one(
			1.f
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				2 * near / w, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, 2 * near / h, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, far / (far - near), near * far / (near - far)
			),
			fcppt::math::matrix::row(
				zero, zero, one, zero
			)
		);
}
