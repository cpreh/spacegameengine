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
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


// TODO: Add a test for bresenham_thick as well

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	bresenham_main
)
{
FCPPT_PP_POP_WARNING

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

	int2_vector_sequence result;

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

	BOOST_REQUIRE_EQUAL(
		result.size(),
		11u
	);

	BOOST_CHECK_EQUAL(
		result[0],
		int2_vector(
			0,
			0
		)
	);

	BOOST_CHECK_EQUAL(
		result[1],
		int2_vector(
			1,
			0
		)
	);

	BOOST_CHECK_EQUAL(
		result[2],
		int2_vector(
			2,
			1
		)
	);

	BOOST_CHECK_EQUAL(
		result[3],
		int2_vector(
			3,
			1
		)
	);

	BOOST_CHECK_EQUAL(
		result[4],
		int2_vector(
			4,
			2
		)
	);

	BOOST_CHECK_EQUAL(
		result[5],
		int2_vector(
			5,
			2
		)
	);

	BOOST_CHECK_EQUAL(
		result[6],
		int2_vector(
			6,
			2
		)
	);

	BOOST_CHECK_EQUAL(
		result[7],
		int2_vector(
			7,
			3
		)
	);

	BOOST_CHECK_EQUAL(
		result[8],
		int2_vector(
			8,
			3
		)
	);

	BOOST_CHECK_EQUAL(
		result[9],
		int2_vector(
			9,
			4
		)
	);

	BOOST_CHECK_EQUAL(
		result[10],
		int2_vector(
			10,
			4
		)
	);
}
