//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy2_comparison.hpp>
#include <fcppt/variant/comparison.hpp>

bool sge::rucksack::operator==(
    sge::rucksack::axis_policy2 const &_left, sge::rucksack::axis_policy2 const &_right)
{
  return _left.x() == _right.x() && _left.y() == _right.y();
}
