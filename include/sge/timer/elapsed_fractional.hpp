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
#include <sge/timer/elapsed.hpp>
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace timer
{
template<typename Float,typename Clock>
typename
boost::enable_if
<
	boost::is_floating_point<Float>,
	Float
>::type
elapsed_fractional(
	timer::basic<Clock> const &t)
{
	typedef fcppt::chrono::duration<
		Float,
		typename Clock::duration::period
	> float_duration;

	return
		timer::elapsed<
			float_duration
		>(
			t)
		/
		t. template interval<
			float_duration
		>();
}
}
}

#endif
