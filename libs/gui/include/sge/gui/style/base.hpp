//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_STYLE_BASE_HPP_INCLUDED
#define SGE_GUI_STYLE_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::style
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
  FCPPT_NONMOVABLE(base);

protected:
  SGE_GUI_DETAIL_SYMBOL
  base();

public:
  SGE_GUI_DETAIL_SYMBOL
  virtual ~base();

  [[nodiscard]] virtual sge::rucksack::dim button_spacing() const = 0;

  virtual void draw_button(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const = 0;

  virtual void draw_bar(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &,
      sge::rucksack::axis,
      sge::gui::fill_level,
      sge::gui::fill_color const &) const = 0;

  [[nodiscard]] virtual sge::rucksack::padding frame_padding() const = 0;

  virtual void draw_frame(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &,
      sge::rucksack::padding) const = 0;

  [[nodiscard]] virtual sge::rucksack::dim edit_spacing() const = 0;

  virtual void draw_edit(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const = 0;

  [[nodiscard]] virtual sge::rucksack::dim image_spacing() const = 0;

  virtual void draw_image(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const = 0;

  [[nodiscard]] virtual sge::rucksack::dim text_spacing() const = 0;

  virtual void draw_text(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const = 0;

  [[nodiscard]] virtual sge::gui::text_color text_color() const = 0;
};

}

#endif
