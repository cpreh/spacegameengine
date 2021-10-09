//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/needed_width.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::gui::widget::text::text(
    sge::gui::style::const_reference const _style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::font::string &&_value,
    sge::gui::text_color _text_color,
    sge::gui::optional_needed_width const _needed_width)
    : sge::gui::widget::base(),
      style_(_style),
      renderer_(_renderer),
      font_(_font),
      text_color_(std::move(_text_color)),
      needed_width_(_needed_width),
      value_(std::move(_value)),
      layout_{sge::rucksack::axis_policy2{
          this->horizontal_policy(),
          sge::rucksack::axis_policy{sge::rucksack::preferred_size{
              font_.get().metrics().height().get() + style_.get().text_spacing().h()}}}}
{
}

FCPPT_PP_POP_WARNING

sge::gui::widget::text::~text() = default;

void sge::gui::widget::text::value(sge::font::string &&_value)
{
  value_ = std::move(_value);

  layout_.axis_policy(
      sge::rucksack::axis_policy2(this->horizontal_policy(), layout_.axis_policy().y()));

  sge::gui::impl::relayout_ancestor(*this);
}

void sge::gui::widget::text::text_color(sge::gui::text_color const &_text_color)
{
  text_color_ = _text_color;
}

sge::rucksack::widget::base &sge::gui::widget::text::layout() { return layout_; }

void sge::gui::widget::text::on_draw(
    sge::gui::renderer::base &_renderer, sge::renderer::context::ffp &_context)
{
  style_.get().draw_text(_renderer, _context, this->layout().area());

  sge::font::draw::static_text const static_text(
      renderer_,
      font_,
      value_,
      sge::font::text_parameters(sge::font::align_h::variant{sge::font::align_h::center(
                                     sge::font::align_h::max_width(layout_.size().w()))})
          .flags(sge::font::flags_field{sge::font::flags::no_multi_line}),
      fcppt::math::vector::structure_cast<sge::font::vector, fcppt::cast::size_fun>(
          layout_.position()) +
          sge::font::vector(
              0, sge::font::v_center(font_.get().metrics().height(), layout_.size().h())),
      text_color_.get(),
      sge::renderer::texture::emulate_srgb::no);

  _renderer.draw_static_text(_context, static_text);
}

sge::rucksack::axis_policy sge::gui::widget::text::horizontal_policy() const
{
  return sge::rucksack::axis_policy{sge::rucksack::preferred_size{
      fcppt::optional::maybe(
          needed_width_,
          [this]
          {
            return font_.get()
                .create_text(
                    value_,
                    sge::font::text_parameters(
                        sge::font::align_h::variant{sge::font::align_h::left()}))
                ->logical_size()
                .w();
          },
          [](sge::gui::needed_width const _needed_width) { return _needed_width.get(); }) +
      style_.get().text_spacing().w()}};
}
