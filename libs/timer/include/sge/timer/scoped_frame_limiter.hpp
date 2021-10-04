//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_SCOPED_FRAME_LIMITER_HPP_INCLUDED
#define SGE_TIMER_SCOPED_FRAME_LIMITER_HPP_INCLUDED

#include <sge/timer/scoped_frame_limiter_fwd.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::timer
{

/**
\brief Force a code block to execute at least a given number of milliseconds

This class is used to artificially limit the frame rate or the duration of one
simulation "tick" to a specified amount of milliseconds.
*/
class scoped_frame_limiter
{
	FCPPT_NONMOVABLE(
		scoped_frame_limiter
	);
public:
	using
	clock_type
	=
	sge::timer::clocks::standard;

	using
	ticks_per_second
	=
	unsigned;

	/**
	\brief Notes the current time for later comparison

	\param ticks Denotes the targeted number of ticks per seconds

	Any frame that's shorter than 1/f will be stalled (by calling sleep, so
	no CPU is consumed).
	*/
	SGE_TIMER_DETAIL_SYMBOL
	explicit
	scoped_frame_limiter(
		ticks_per_second ticks
	);

	/**
	\brief Compares the stored time with the current time and calls sleep
	*/
	SGE_TIMER_DETAIL_SYMBOL
	~scoped_frame_limiter();
private:
	clock_type::time_point const before_frame_;

	clock_type::duration minimum_frame_length_;
};

}

#endif
