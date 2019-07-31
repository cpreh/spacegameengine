//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/timer/absolute.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/difference_and_reset.hpp>
#include <sge/timer/difference_fractional.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/remaining.hpp>
#include <sge/timer/clocks/delta.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
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
