//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp> // NOLINT(misc-include-cleaner)
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/bar.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/access_axis.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp> // NOLINT(misc-include-cleaner)
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::gui::widget::bar::bar(
    sge::gui::style::const_reference const _style,
    sge::rucksack::dim const &_dim,
    sge::rucksack::axis const _axis,
    sge::gui::fill_color _foreground,
    sge::gui::fill_level const _value)
    : sge::gui::widget::base(),
      style_(_style),
      axis_{_axis},
      foreground_(std::move(_foreground)),
      value_(_value),
      layout_{sge::rucksack::make_axis_policy(sge::rucksack::axis_policy_function{
          [_axis, _dim](sge::rucksack::axis const _cur_axis)
          {
            sge::rucksack::scalar const ret{sge::rucksack::access_axis(_dim, _cur_axis)};

            return _axis == _cur_axis
                       ? sge::rucksack::axis_policy{sge::rucksack::minimum_size{ret}}
                       : sge::rucksack::axis_policy{sge::rucksack::preferred_size{ret}};
          }})}
{
}

sge::gui::widget::bar::~bar() = default;

void sge::gui::widget::bar::value(sge::gui::fill_level const _value) { value_ = _value; }

void sge::gui::widget::bar::on_draw(
    sge::gui::renderer::base &_renderer, sge::renderer::context::ffp &_render_context)
{
  style_.get().draw_bar(
      _renderer, _render_context, this->layout().area(), axis_, value_, foreground_);
}

sge::rucksack::widget::base &sge::gui::widget::bar::layout() { return layout_; }
