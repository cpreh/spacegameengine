/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIMER_SCOPED_FRAME_LIMITER_HPP_INCLUDED
#define SGE_TIMER_SCOPED_FRAME_LIMITER_HPP_INCLUDED

#include <sge/timer/scoped_frame_limiter_fwd.hpp>
#include <sge/timer/symbol.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace timer
{
/**
\brief Force a code block to execute at least a given number of milliseconds

This class is used to artificially limit the frame rate or the duration of one
simulation "tick" to a specified amount of milliseconds.
*/
class scoped_frame_limiter
{
	FCPPT_NONCOPYABLE(
		scoped_frame_limiter
	);
public:
	typedef
	sge::timer::clocks::standard
	clock_type;

	typedef
	unsigned
	ticks_per_second;

	/**
	\brief Notes the current time for later comparison

	\param ticks Denotes the targeted number of ticks per seconds

	Any frame that's shorter than 1/f will be stalled (by calling sleep, so
	no CPU is consumed).
	*/
	SGE_TIMER_SYMBOL
	explicit
	scoped_frame_limiter(
		ticks_per_second ticks
	);

	/**
	\brief Compares the stored time with the current time and calls sleep
	*/
	SGE_TIMER_SYMBOL
	~scoped_frame_limiter();
private:
	clock_type::time_point const before_frame_;

	clock_type::duration minimum_frame_length_;
};

}
}

#endif
