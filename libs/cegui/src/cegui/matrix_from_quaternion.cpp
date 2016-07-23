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
#include <sge/src/cegui/matrix_from_quaternion.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Quaternion.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::matrix4
sge::cegui::matrix_from_quaternion(
	CEGUI::Quaternion const _quat
)
{
	sge::renderer::scalar const
		s = _quat.d_w,
		x = _quat.d_x,
		y = _quat.d_y,
		z = _quat.d_z;

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				1-2*(y*y + z*z), 2*x*y-2*s*z, 2*s*y + 2*x*z, 0.f
			),
			fcppt::math::matrix::row(
				2*x*y+2*s*z, 1-2*(x*x + z*z),-2*s*x+2*y*z,0.f
			),
			fcppt::math::matrix::row(
				-2*s*y + 2*x*z,2*s*x+2*y*z,1-2*(x*x+y*y),0.f
			),
			fcppt::math::matrix::row(
				0.f,0.f,0.f,1.f
			)
		);
}
