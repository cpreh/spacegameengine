//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/context_ref.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/container.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_vector.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/map.hpp>

sge::gui::widget::box_container::box_container(
    sge::gui::context_ref const _context,
    sge::gui::widget::reference_alignment_vector const &_widgets,
    sge::rucksack::axis const _axis)
    : sge::gui::widget::container(
          _context,
          fcppt::algorithm::map<sge::gui::widget::reference_vector>(
              _widgets,
              [](sge::gui::widget::reference_alignment_pair const &_pair)
              { return _pair.reference(); }),
          // This is pretty dangerous but the base class only uses the
          // reference here
          fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(layout_))),
      layout_(_axis, sge::rucksack::padding{4})
{
  for (auto const &element : _widgets)
  {
    layout_.push_back_child(
        fcppt::make_ref(element.reference().get().layout()), element.alignment());
  }
}

sge::gui::widget::box_container::~box_container() = default;

void sge::gui::widget::box_container::push_front(
    sge::gui::widget::reference_alignment_pair const &_pair)
{
  this->push_front_widget(_pair.reference());

  layout_.push_front_child(fcppt::make_ref(_pair.reference().get().layout()), _pair.alignment());
}

void sge::gui::widget::box_container::pop_front()
{
  layout_.pop_front_child();

  this->pop_front_widget();
}

void sge::gui::widget::box_container::push_back(
    sge::gui::widget::reference_alignment_pair const &_pair)
{
  this->push_back_widget(_pair.reference());

  layout_.push_back_child(fcppt::make_ref(_pair.reference().get().layout()), _pair.alignment());
}

void sge::gui::widget::box_container::replace(
    sge::rucksack::widget::box::size_type const _index,
    sge::gui::widget::reference_alignment_pair const &_pair)
{
  this->replace_widgets(_index, _pair.reference());

  layout_.replace_children(
      layout_.child_position(_index),
      fcppt::make_ref(_pair.reference().get().layout()),
      _pair.alignment());
}

void sge::gui::widget::box_container::pop_back()
{
  layout_.pop_back_child();

  this->pop_back_widget();
}

void sge::gui::widget::box_container::clear()
{
  layout_.clear();

  this->clear_widgets();
}

sge::rucksack::widget::box &sge::gui::widget::box_container::box_layout() { return layout_; }
