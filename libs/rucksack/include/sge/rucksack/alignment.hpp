//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_ALIGNMENT_HPP_INCLUDED
#define SGE_RUCKSACK_ALIGNMENT_HPP_INCLUDED

#include <sge/rucksack/alignment_fwd.hpp> // IWYU pragma: keep

namespace sge::rucksack
{

enum class alignment
{
  left_or_top,
  center,
  right_or_bottom,
  fcppt_maximum = right_or_bottom
};

}

#endif
