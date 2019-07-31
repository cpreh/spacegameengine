//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/bresenham/normal.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


// TODO: Add a test for bresenham_thick as well

TEST_CASE(
	"bresenham",
	"[sge]"
)
{
	typedef
	fcppt::math::vector::static_<
		int,
		2
	>
	int2_vector;

	typedef
	std::vector<
		int2_vector
	>
	int2_vector_sequence;

	int2_vector_sequence result{};

	sge::bresenham::normal(
		int2_vector(
			0,
			0
		),
		int2_vector(
			10,
			4
		),
		[
			&result
		](
			int2_vector const _vec
		)
		{
			result.push_back(
				_vec
			);

			return
				true;
		}
	);

	CHECK(
		result
		==
		int2_vector_sequence{
			int2_vector(
				0,
				0
			),
			int2_vector(
				1,
				0
			),
			int2_vector(
				2,
				1
			),
			int2_vector(
				3,
				1
			),
			int2_vector(
				4,
				2
			),
			int2_vector(
				5,
				2
			),
			int2_vector(
				6,
				2
			),
			int2_vector(
				7,
				3
			),
			int2_vector(
				8,
				3
			),
			int2_vector(
				9,
				4
			),
			int2_vector(
				10,
				4
			)
		}
	);
}
