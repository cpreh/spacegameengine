//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/math/size_type.hpp>

fcppt::math::size_type sge::rucksack::axis_to_index(sge::rucksack::axis const _axis)
{
  return fcppt::cast::enum_to_int<fcppt::math::size_type>(_axis);
}
