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


#include "convert_normal.hpp"
#include "vec3.hpp"
#include <sge/model/md3/scalar.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <cmath>

sge::model::md3::vec3 const
sge::model::md3::convert_normal(
	md3::s16 const _normal
)
{
	md3::scalar const
		lat(
			static_cast<
				md3::scalar
			>(
				(_normal >> 8)
				& 255
			)
			*
			fcppt::math::twopi<
				md3::scalar
			>()
			/ 255
		),
		lng(
			static_cast<
				md3::scalar
			>(
				_normal & 255
			)
			*
			fcppt::math::twopi<
				md3::scalar
			>()
			/ 255
		);

	return
		md3::vec3(
			std::cos(lat) * std::sin(lng),
			std::sin(lat) * std::sin(lng),
			std::cos(lng)
		);
}
