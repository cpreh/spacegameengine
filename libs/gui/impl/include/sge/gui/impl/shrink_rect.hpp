//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_IMPL_SHRINK_RECT_HPP_INCLUDED
#define SGE_GUI_IMPL_SHRINK_RECT_HPP_INCLUDED

#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/scalar.hpp>

namespace sge::gui::impl
{

[[nodiscard]] sge::rucksack::rect shrink_rect(sge::rucksack::rect const &, sge::rucksack::scalar);

}

#endif
