//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_SIMPLE_HPP_INCLUDED

#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::impl::style
{

class simple : public sge::gui::style::base
{
  FCPPT_NONMOVABLE(simple);

public:
  simple();

  ~simple() override;

private:
  [[nodiscard]] sge::rucksack::dim button_spacing() const override;

  void draw_button(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const override;

  void draw_bar(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &,
      sge::rucksack::axis,
      sge::gui::fill_level,
      sge::gui::fill_color const &) const override;

  [[nodiscard]] sge::rucksack::padding frame_padding() const override;

  void draw_frame(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &,
      sge::rucksack::padding) const override;

  [[nodiscard]] sge::rucksack::dim edit_spacing() const override;

  void draw_edit(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const override;

  [[nodiscard]] sge::rucksack::dim image_spacing() const override;

  void draw_image(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const override;

  [[nodiscard]] sge::rucksack::dim text_spacing() const override;

  void draw_text(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) const override;

  [[nodiscard]] sge::gui::text_color text_color() const override;

  [[nodiscard]] static sge::rucksack::dim spacing();
};

}

#endif
