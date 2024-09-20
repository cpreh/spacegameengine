//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_AXIS_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_HPP_INCLUDED

#include <sge/rucksack/axis_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack
{

enum class axis : std::uint8_t
{
  x,
  y
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::rucksack::axis::y);

#endif
