/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/math/atan2.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/vector/vector.hpp>
#include <sge/math/matrix/matrix.hpp>
#include <sge/math/matrix/dynamic_impl.hpp>
#include <sge/math/dim/dim.hpp>
#include <sge/math/point_rotate.hpp>
#include <sge/cin.hpp>
#include <sge/cout.hpp>
#include <boost/assign/list_of.hpp>
#include <istream>
#include <ostream>

int main()
{
	sge::math::vector::static_<
		int,
		2
	>::type vec(
		1,
		2);
	
	sge::math::angle_to<float>(
		vec,
		vec);
	
	sge::math::vector::static_<
		float,
		2
	>::type const vecf(
		static_cast<float>(1),
		static_cast<float>(2));
	
	sge::math::atan2(vecf);

	sge::math::point_rotate(
		vecf,
		vecf,
		3.f);
	
	typedef sge::math::matrix::dynamic<
		float
	>::type dynamic_float_matrix;

	dynamic_float_matrix matrix(
		dynamic_float_matrix::dim_type(
			2,
			3),
		boost::assign::list_of
			(0)(0)
			(1)(1)
			(2)(2));

	normalize(vecf);

	//sge::cin >> vec;

	sge::cout
		<< vec << SGE_TEXT('\n')
		<< sge::math::vector::length<float>(vec) << SGE_TEXT('\n')
		<< length(vecf) << SGE_TEXT('\n');
	
	typedef sge::math::vector::static_<
		double,
		3
	>::type vec3d;

	{
		vec3d
			a(
				1.0,
				0.0,
				0.0
			),
			b(
				0.0,
				1.0,
				0.0
			),
			c(
				0.0,
				0.0,
				-1.0
			);

		normalize(a);
		normalize(b);
		normalize(c);

		sge::cout << cross(a, b) << SGE_TEXT(' ') << c << SGE_TEXT('\n');
	}
}
