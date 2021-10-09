//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_WIDGET_BUTTON_HPP_INCLUDED
#define SGE_GUI_WIDGET_BUTTON_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/click_function.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/optional_needed_width_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/button_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>

namespace sge::gui::widget
{

class button : public sge::gui::widget::base
{
  FCPPT_NONMOVABLE(button);

public:
  SGE_GUI_DETAIL_SYMBOL
  button(
      sge::gui::style::const_reference,
      sge::renderer::device::ffp_ref,
      sge::font::object_ref,
      sge::font::string const &,
      sge::gui::optional_needed_width);

  SGE_GUI_DETAIL_SYMBOL
  ~button() override;

  [[nodiscard]] SGE_GUI_DETAIL_SYMBOL fcppt::signal::auto_connection
  click(sge::gui::click_callback &&);

  [[nodiscard]] SGE_GUI_DETAIL_SYMBOL sge::font::string const &text() const;

  SGE_GUI_DETAIL_SYMBOL
  void text(sge::font::string const &);

  [[nodiscard]] SGE_GUI_DETAIL_SYMBOL sge::rucksack::widget::base &layout() override;

private:
  void on_draw(sge::gui::renderer::base &, sge::renderer::context::ffp &) override;

  [[nodiscard]] sge::gui::get_focus on_click(sge::rucksack::vector const &) override;

  [[nodiscard]] sge::font::draw::static_text make_static_text(sge::font::string const &);

  sge::gui::style::const_reference const style_;

  sge::renderer::device::ffp_ref const renderer_;

  sge::font::object_ref const font_;

  sge::font::string text_;

  sge::font::draw::static_text static_text_;

  sge::rucksack::widget::dummy layout_;

  using click_signal = fcppt::signal::object<sge::gui::click_function>;

  click_signal click_;
};

}

#endif
