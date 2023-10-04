//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/preferred_size.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>

sge::gui::widget::preferred_size::preferred_size(sge::rucksack::dim const &_area)
    : sge::gui::widget::dummy(),
      layout_{sge::rucksack::axis_policy2{
          sge::rucksack::axis_policy{sge::rucksack::preferred_size{_area.w()}},
          sge::rucksack::axis_policy{sge::rucksack::preferred_size{_area.h()}}}}
{
}

sge::gui::widget::preferred_size::~preferred_size() = default;

sge::rucksack::widget::base &sge::gui::widget::preferred_size::layout() { return layout_; }
