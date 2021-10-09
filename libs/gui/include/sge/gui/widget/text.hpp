//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_WIDGET_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGET_TEXT_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/text_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/axis_policy_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::widget
{

class text : public sge::gui::widget::base
{
  FCPPT_NONMOVABLE(text);

public:
  SGE_GUI_DETAIL_SYMBOL
  text(
      sge::gui::style::const_reference,
      sge::renderer::device::ffp_ref,
      sge::font::object_ref,
      sge::font::string &&,
      sge::gui::text_color,
      sge::gui::optional_needed_width);

  SGE_GUI_DETAIL_SYMBOL
  ~text() override;

  SGE_GUI_DETAIL_SYMBOL
  void value(sge::font::string &&);

  SGE_GUI_DETAIL_SYMBOL
  void text_color(sge::gui::text_color const &);

  [[nodiscard]] SGE_GUI_DETAIL_SYMBOL sge::rucksack::widget::base &layout() override;

private:
  void on_draw(sge::gui::renderer::base &, sge::renderer::context::ffp &) override;

  [[nodiscard]] sge::rucksack::axis_policy horizontal_policy() const;

  sge::gui::style::const_reference const style_;

  sge::renderer::device::ffp_ref const renderer_;

  sge::font::object_ref const font_;

  sge::gui::text_color text_color_;

  sge::gui::optional_needed_width const needed_width_;

  sge::font::string value_;

  sge::rucksack::widget::dummy layout_;
};

}

#endif
