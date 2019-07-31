//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <fcppt/math/vector/object.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <array>
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

	CHECK(
		result.size()
		==
		_points.size() - 2u
	);

	// FIXME
}

}

TEST_CASE(
	"projectile::triangulate_long",
	"[sge]"
)
{
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
