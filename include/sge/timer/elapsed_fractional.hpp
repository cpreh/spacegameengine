/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace timer
{
template<typename Float,typename Duration,typename Clock>
typename
boost::enable_if
<
	boost::is_floating_point<Float>,
	Float
>::type
elapsed_fractional(
	timer::basic<Duration,Clock> const &t)
{
	if(!t.active())
		return 
			static_cast<Float>(
				0);

	if(t.expired())
		return 
			static_cast<Float>(
				1);

	return 
		static_cast<Float>((t.callback()() - t.last_time()).count()) / 
		static_cast<Float>(
			fcppt::chrono::duration_cast<typename Clock::duration>(
				t.interval()).count());
}
}
}

#endif
