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
