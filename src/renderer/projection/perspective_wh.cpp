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


#include <sge/renderer/projection/perspective_wh.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/text.hpp>

sge::renderer::matrix4 const
sge::renderer::projection::perspective_wh(
	projection::dim const &_dim,
	projection::near const _far,
	projection::far const _near
)
{
	sge::renderer::scalar const
		far(
			_far.get()
		),
		near(
			_near.get()
		);

	if(
		fcppt::math::compare(
			far,
			near
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("projection::perspective(): far may not be near!")
		);

	if(
		fcppt::math::almost_zero(
			near
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("matrix::perspective(): near must not be 0!")
		);

	sge::renderer::scalar const
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
			2 * near / w, zero, zero, zero,
			zero, 2 * near / h, zero, zero,
			zero, zero, far / (far - near), near * far / (near - far),
			zero, zero, one, zero
		);
}
