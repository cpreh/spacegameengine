//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_DETAIL_WRAPPER_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DETAIL_WRAPPER_HPP_INCLUDED

#include <sge/timer/clocks/is_stateful.hpp>
#include <sge/timer/clocks/detail/stateful_base.hpp>
#include <sge/timer/clocks/detail/stateless_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{
namespace detail
{

template<
	typename Clock
>
using wrapper
=
std::conditional_t<
	sge::timer::clocks::is_stateful<
		Clock
	>::value,
	sge::timer::clocks::detail::stateful_base<
		Clock
	>,
	sge::timer::clocks::detail::stateless_base<
		Clock
	>
>;

}
}
}
}

#endif
