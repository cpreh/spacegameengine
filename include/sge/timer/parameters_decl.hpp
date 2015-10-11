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


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/parameters_fwd.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace timer
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Clock
>
class parameters final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	FCPPT_NONASSIGNABLE(
		parameters
	);

	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	state_base;
public:
	typedef
	Clock
	clock_type;

	typedef
	typename
	clock_type::duration
	duration;

	template<
		typename Duration
	>
	explicit
	parameters(
		Duration const &
	);

	template<
		typename Duration
	>
	parameters(
		clock_type const &,
		Duration const &
	);

	parameters &
	active(
		bool
	);

	parameters &
	expired(
		bool
	);

	duration
	interval() const;

	state_base const &
	clock() const;

	bool
	active() const;

	bool
	expired() const;
private:
	duration const interval_;

	bool active_;

	bool expired_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
