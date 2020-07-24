//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_MAKE_AXIS_POLICY_HPP_INCLUDED
#define SGE_RUCKSACK_MAKE_AXIS_POLICY_HPP_INCLUDED

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/detail/symbol.hpp>


namespace sge
{
namespace rucksack
{

SGE_RUCKSACK_DETAIL_SYMBOL
sge::rucksack::axis_policy2
make_axis_policy(
	sge::rucksack::axis_policy_function const &
);

}
}

#endif
