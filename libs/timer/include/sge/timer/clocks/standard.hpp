//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_STANDARD_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_STANDARD_HPP_INCLUDED

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

typedef
std::conditional<
	std::chrono::high_resolution_clock::is_steady,
	std::chrono::high_resolution_clock,
	std::chrono::steady_clock
>::type
standard;

}
}
}

#endif
