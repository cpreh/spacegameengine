/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <fcppt/math/vector/object.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <array>
#include <iostream>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef long unit;

typedef fcppt::math::vector::static_<
	unit,
	2
> vector2;

typedef std::array<
	vector2,
	3
> triangle;

typedef std::vector<
	triangle
> triangle_sequence;

typedef std::vector<
	vector2
> point_sequence;


void
test_long(
	point_sequence const &_points,
	unit const _epsilon
)
{
	triangle_sequence const result(
		sge::projectile::triangulation::triangulate<
			sge::projectile::triangulation::default_tag,
			triangle_sequence
		>(
			_points,
			_epsilon
		)
	);

	BOOST_CHECK(
		result.size()
		==
		_points.size() - 2u
	);

	std::cout
		<< "Triangulating "
		<< _points.size()
		<< " points:\n\t";

	for(
		point_sequence::const_iterator it(
			_points.begin()
		);
		it != _points.end();
		++it
	)
		std::cout
			<< *it
			<< ' ';

	std::cout
		<< "\nResult has "
		<< result.size()
		<< " triangles:\n";

	for(
		triangle_sequence::const_iterator it(
			result.begin()
		);
		it != result.end();
		++it
	)
	{
		std::cout << '\t';

		for(
			triangle::const_iterator t_it(
				it->begin()
			);
			t_it != it->end();
			++t_it
		)
			std::cout
				<< *t_it
				<< ' ';

		std::cout << '\n';
	}

	std::cout << '\n';
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	projectile_triangulate_long
)
{
FCPPT_PP_POP_WARNING

	test_long(
		point_sequence{
			vector2(
				0,
				0
			),
			vector2(
				100,
				0
			),
			vector2(
				100,
				100
			),
			vector2(
				0,
				100
			)
		}
		,
		0l
	);

	test_long(
		point_sequence{
			vector2(
				0,
				0
			),
			vector2(
				0,
				1000
			),
			vector2(
				2000,
				2000
			),
			vector2(
				1000,
				500
			)
		}
		,
		0l
	);
}
