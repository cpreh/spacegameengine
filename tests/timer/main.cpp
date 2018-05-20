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


#include <sge/timer/absolute.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/difference_and_reset.hpp>
#include <sge/timer/difference_fractional.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/remaining.hpp>
#include <sge/timer/clocks/delta.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"timer::basic",
	"[sge]"
)
{
	typedef
	sge::timer::clocks::delta<
		std::chrono::milliseconds
	>
	clock;

	clock clk{};

	typedef
	sge::timer::basic<
		clock
	>
	timer;

	timer t1{
		timer::parameters{
			clk,
			std::chrono::seconds(
				0
			)
		}
	};

	CHECK(
		t1.interval()
		==
		std::chrono::seconds(
			0
		)
	);

	CHECK(
		t1.expired()
	);

	t1.interval(
		std::chrono::seconds(
			1
		)
	);

	t1.reset();

	CHECK_FALSE(
		t1.expired()
	);

	CHECK(
		sge::timer::remaining(
			t1
		)
		==
		std::chrono::seconds(
			1
		)
	);

	clk.update(
		std::chrono::seconds(
			2
		)
	);

	CHECK(
		sge::timer::elapsed(
			t1
		)
		==
		std::chrono::seconds(
			1
		)
	);

	CHECK(
		sge::timer::difference_fractional<
			float
		>(
			t1
		)
		>=
		1.9f
	);
}

TEST_CASE(
	"timer::absolute",
	"[sge]"
)
{
	typedef
	sge::timer::clocks::delta<
		std::chrono::milliseconds
	>
	clock;

	clock clk;

	typedef
	sge::timer::absolute<
		clock
	>
	absolute;

	absolute t1{
		clk
	};

	CHECK(
		sge::timer::difference(
			t1
		)
		==
		std::chrono::seconds(
			0
		)
	);

	clk.update(
		std::chrono::seconds(
			2
		)
	);

	CHECK(
		sge::timer::difference_and_reset(
			t1
		)
		==
		std::chrono::seconds(
			2
		)
	);

	CHECK(
		sge::timer::difference(
			t1
		)
		==
		std::chrono::seconds(
			0
		)
	);
}
