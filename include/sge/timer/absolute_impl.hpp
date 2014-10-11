/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TIMER_ABSOLUTE_IMPL_HPP_INCLUDED
#define SGE_TIMER_ABSOLUTE_IMPL_HPP_INCLUDED

#include <sge/timer/absolute_decl.hpp>
#include <sge/timer/clocks/is_stateful.hpp>


template<
	typename Clock
>
sge::timer::absolute<
	Clock
>::absolute()
:
	absolute(
		clock_type()
	)
{
	static_assert(
		!sge::timer::clocks::is_stateful<
			Clock
		>::value,
		"Stateful clocks need to be passed as parameters"
	);
}

template<
	typename Clock
>
sge::timer::absolute<
	Clock
>::absolute(
	Clock const &_clock
)
:
	base(
		_clock
	),
	last_time_{
		this->now()
	}
{
}

template<
	typename Clock
>
typename
sge::timer::absolute<
	Clock
>::time_point const
sge::timer::absolute<
	Clock
>::now() const
{
	return
		this->clock_base().now();
}

template<
	typename Clock
>
typename
sge::timer::absolute<
	Clock
>::time_point const
sge::timer::absolute<
	Clock
>::last_time() const
{
	return
		last_time_;
}

template<
	typename Clock
>
void
sge::timer::absolute<
	Clock
>::reset()
{
	last_time_ =
		this->now();
}

#endif
