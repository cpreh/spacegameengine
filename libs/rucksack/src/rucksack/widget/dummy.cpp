//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>

sge::rucksack::widget::dummy::dummy(sge::rucksack::axis_policy2 const &_axis_policy)
    : sge::rucksack::widget::base(),
      axis_policy_{_axis_policy},
      position_{fcppt::math::vector::null<sge::rucksack::vector>()},
      size_{fcppt::math::dim::null<sge::rucksack::dim>()}
{
}

void sge::rucksack::widget::dummy::size(sge::rucksack::dim const &_size) { size_ = _size; }

void sge::rucksack::widget::dummy::position(sge::rucksack::vector const &_position)
{
  position_ = _position;
}

void sge::rucksack::widget::dummy::axis_policy(sge::rucksack::axis_policy2 const &_axis_policy)
{
  axis_policy_ = _axis_policy;
}

sge::rucksack::dim sge::rucksack::widget::dummy::size() const { return size_; }

sge::rucksack::vector sge::rucksack::widget::dummy::position() const { return position_; }

sge::rucksack::axis_policy2 sge::rucksack::widget::dummy::axis_policy() const
{
  return axis_policy_;
}

void sge::rucksack::widget::dummy::relayout() {}

sge::rucksack::widget::dummy::~dummy() = default;
