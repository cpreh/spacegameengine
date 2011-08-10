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


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/clocks/detail/wrapper.hpp>
#include <sge/timer/detail/parameters_base_decl.hpp>
#include <sge/timer/enable_ctor_stateful.hpp>
#include <sge/timer/enable_ctor_stateless.hpp>
#include <sge/timer/parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace timer
{
template<typename Clock>
class parameters
:
	timer::clocks::detail::wrapper<
		Clock
	>::type,
	timer::detail::parameters_base<
		Clock
	>
{
FCPPT_NONASSIGNABLE(
	parameters);

	typedef typename timer::clocks::detail::wrapper<
		Clock
	>::type state_base;

	typedef timer::detail::parameters_base<
		Clock
	> parameters_base;
public:
	typedef
	Clock
	clock_type;

	typedef
	typename parameters_base::duration
	duration;

	template<
		typename Duration>
	explicit
	parameters(
		clock_type const &,
		Duration const &,
		typename timer::enable_ctor_stateful<
			Clock,
			Duration
		>::type const * = 0);

	template<
		typename Duration>
	explicit
	parameters(
		Duration const &,
		typename timer::enable_ctor_stateless<
			Clock,
			Duration
		>::type const * = 0);

	parameters &
	active(
		bool);

	parameters &
	expired(
		bool);

	duration const
	interval() const;

	state_base const &
	clock() const;

	bool
	active() const;

	bool
	expired() const;
};
}
}

#endif
