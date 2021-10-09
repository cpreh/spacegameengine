//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/impl/flip_axis.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::rucksack::axis sge::rucksack::impl::flip_axis(sge::rucksack::axis const _axis)
{
  switch (_axis)
  {
  case sge::rucksack::axis::x:
    return sge::rucksack::axis::y;
  case sge::rucksack::axis::y:
    return sge::rucksack::axis::x;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
