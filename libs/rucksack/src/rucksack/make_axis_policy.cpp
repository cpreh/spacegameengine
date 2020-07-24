//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/make_axis_policy.hpp>


sge::rucksack::axis_policy2
sge::rucksack::make_axis_policy(
	sge::rucksack::axis_policy_function const &_function
)
{
	return
		sge::rucksack::axis_policy2{
			_function(
				sge::rucksack::axis::x
			),
			_function(
				sge::rucksack::axis::y
			)
		};
}
