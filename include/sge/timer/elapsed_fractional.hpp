/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TIMER_ELAPSED_FRACTIONAL_HPP_INCLUDED
#define SGE_TIMER_ELAPSED_FRACTIONAL_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/interval.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <chrono>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{

template<
	typename Float,
	typename Clock
>
typename
boost::enable_if<
	std::is_floating_point<
		Float
	>,
	Float
>::type
elapsed_fractional(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	typedef
	std::chrono::duration<
		Float,
		typename Clock::period
	>
	float_duration;

	return
		sge::timer::elapsed<
			float_duration
		>(
			_timer
		)
		/
		sge::timer::interval<
			float_duration
		>(
			_timer
		);
}

}
}

#endif
