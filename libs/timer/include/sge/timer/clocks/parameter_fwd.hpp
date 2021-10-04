//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_PARAMETER_FWD_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_PARAMETER_FWD_HPP_INCLUDED

#include <sge/timer/clocks/is_stateful.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::timer::clocks
{

template<
	typename Clock
>
using
parameter
=
std::conditional_t<
	sge::timer::clocks::is_stateful<
		Clock
	>::value,
	fcppt::reference<
		Clock const
	>,
	Clock const &
>;

}

#endif
