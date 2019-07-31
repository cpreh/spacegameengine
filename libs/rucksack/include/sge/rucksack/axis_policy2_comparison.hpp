//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_AXIS_POLICY2_COMPARISON_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY2_COMPARISON_HPP_INCLUDED

#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/detail/symbol.hpp>


namespace sge
{
namespace rucksack
{

SGE_RUCKSACK_DETAIL_SYMBOL
bool
operator==(
	sge::rucksack::axis_policy2 const &,
	sge::rucksack::axis_policy2 const &
);

}
}

#endif
