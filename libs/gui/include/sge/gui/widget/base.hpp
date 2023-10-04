//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_WIDGET_BASE_HPP_INCLUDED
#define SGE_GUI_WIDGET_BASE_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change_fwd.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::widget
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  SGE_GUI_DETAIL_SYMBOL
  virtual ~base();

  virtual void on_update(sge::gui::duration);

  virtual void on_draw(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp & // NOLINT(google-runtime-references)
      ) = 0; // NOLINT(google-runtime-references)

  [[nodiscard]] virtual sge::gui::get_focus on_click(sge::rucksack::vector const &);

  virtual void on_key(sge::input::key::code);

  virtual void on_char(sge::font::char_type);

  virtual void on_focus_changed(sge::gui::focus_change);

  [[nodiscard]] virtual sge::gui::widget::optional_ref on_tab(sge::gui::widget::optional_focus_ref);

  [[nodiscard]] virtual sge::rucksack::widget::base &layout() = 0;

  void parent(sge::gui::widget::optional_ref);

  SGE_GUI_DETAIL_SYMBOL
  void enable(bool);

  [[nodiscard]] SGE_GUI_DETAIL_SYMBOL bool enabled() const;

private:
  virtual void unregister(sge::gui::widget::base const &);

  sge::gui::widget::optional_ref parent_;

  bool enabled_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
