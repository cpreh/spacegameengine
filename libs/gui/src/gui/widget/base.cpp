//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/char_type.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>

sge::gui::widget::base::base() : parent_(), enabled_{true} {}

sge::gui::widget::base::~base()
{
  fcppt::optional::maybe_void(
      parent_,
      [this](fcppt::reference<sge::gui::widget::base> const _parent)
      { _parent.get().unregister(*this); });
}

void sge::gui::widget::base::on_update(sge::gui::duration) {}

sge::gui::get_focus sge::gui::widget::base::on_click(sge::rucksack::vector const &)
{
  return sge::gui::get_focus(false);
}

void sge::gui::widget::base::on_key(sge::input::key::code) {}

void sge::gui::widget::base::on_char(sge::font::char_type) {}

void sge::gui::widget::base::on_focus_changed(sge::gui::focus_change) {}

sge::gui::widget::optional_ref sge::gui::widget::base::on_tab(sge::gui::widget::optional_focus_ref)
{
  return sge::gui::widget::optional_ref();
}

void sge::gui::widget::base::parent(sge::gui::widget::optional_ref const _new_parent)
{
  if (parent_.has_value())
  {
    this->layout().parent(sge::rucksack::widget::optional_ref());
  }

  parent_ = _new_parent;

  fcppt::optional::maybe_void(
      _new_parent,
      [this](fcppt::reference<sge::gui::widget::base> const _parent)
      {
        this->layout().parent(
            sge::rucksack::widget::optional_ref(fcppt::make_ref(_parent.get().layout())));
      });
}

void sge::gui::widget::base::enable(bool const _enabled) { enabled_ = _enabled; }

bool sge::gui::widget::base::enabled() const { return enabled_; }

void sge::gui::widget::base::unregister(sge::gui::widget::base const &) {}
