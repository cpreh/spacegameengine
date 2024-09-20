//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_ALIGNMENT_HPP_INCLUDED
#define SGE_RUCKSACK_ALIGNMENT_HPP_INCLUDED

#include <sge/rucksack/alignment_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack
{

enum class alignment : std::uint8_t
{
  left_or_top,
  center,
  right_or_bottom
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::rucksack::alignment::right_or_bottom);

#endif
