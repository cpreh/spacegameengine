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


#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <boost/type_traits/make_signed.hpp>

sge::renderer::matrix4 const
sge::renderer::matrix_pixel_to_space(
	renderer::screen_size const &_sz
)
{
	typedef sge::renderer::matrix4::value_type value_type;

	typedef boost::make_signed<
		renderer::screen_size::value_type
	>::type signed_screen_unit;

	return
		fcppt::math::matrix::scaling(
			2.f
			/ static_cast<
				value_type
			>(
				_sz.w()
			),
			-2.f
			/ static_cast<
				value_type
			>(
				_sz.h()
			),
			1.f
		)
		*
		fcppt::math::matrix::translation(
			static_cast<
				value_type
			>(
				-static_cast<
					signed_screen_unit
				>(
					_sz.w()
				) / 2
			),
			static_cast<
				value_type
			>(
				-static_cast<
					signed_screen_unit
				>(
					_sz.h()
				) / 2
			),
			0.f
		);
}
