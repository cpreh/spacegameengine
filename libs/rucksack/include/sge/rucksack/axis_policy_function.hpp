//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_AXIS_POLICY_FUNCTION_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY_FUNCTION_HPP_INCLUDED

#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/axis_policy_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace rucksack
{

typedef
fcppt::function<
	sge::rucksack::axis_policy (
		sge::rucksack::axis
	)
>
axis_policy_function;

}
}

#endif
