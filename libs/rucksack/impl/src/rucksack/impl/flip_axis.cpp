//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/impl/flip_axis.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::rucksack::axis sge::rucksack::impl::flip_axis(sge::rucksack::axis const _axis)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_axis)
  {
  case sge::rucksack::axis::x:
    return sge::rucksack::axis::y;
  case sge::rucksack::axis::y:
    return sge::rucksack::axis::x;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_axis);
}
