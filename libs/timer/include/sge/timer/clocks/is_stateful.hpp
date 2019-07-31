//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{

template<
	typename Clock,
	typename Enable = void
>
struct is_stateful
:
std::true_type
{
};

template<
	typename Clock
>
struct is_stateful<
	Clock,
	std::enable_if_t<
		std::is_same<
			std::chrono::high_resolution_clock,
			Clock
		>::value
		||
		std::is_same<
			std::chrono::steady_clock,
			Clock
		>::value
		||
		std::is_same<
			std::chrono::system_clock,
			Clock
		>::value
	>
>
:
std::false_type
{
};

}
}
}

#endif
