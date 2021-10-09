//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/char_type.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/index.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/exception.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/text_callback.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/text_function.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/edit.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <sge/timer/clocks/delta_impl.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string_conv_locale.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <locale>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::gui::widget::edit::edit(
    sge::gui::style::const_reference const _style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::font::string &&_text)
    : sge::gui::widget::base(),
      style_(_style),
      renderer_(_renderer),
      font_(_font),
      text_(std::move(_text)),
      position_{0U},
      layout_{sge::rucksack::axis_policy2{
          sge::rucksack::axis_policy{sge::rucksack::minimum_size{_style.get().edit_spacing().w()}},
          sge::rucksack::axis_policy{sge::rucksack::preferred_size{
              font_.get().metrics().height().get() + _style.get().edit_spacing().h()}}}},
      static_text_(this->make_static_text()),
      clock_(),
      cursor_blink_timer_(diff_timer::parameters(
          fcppt::make_cref(clock_),
          std::chrono::milliseconds(
              500 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))),
      has_focus_(false),
      show_cursor_(true),
      text_change_()
{
}

FCPPT_PP_POP_WARNING

sge::gui::widget::edit::~edit() = default;

sge::font::string const &sge::gui::widget::edit::text() const { return text_; }

fcppt::signal::auto_connection
sge::gui::widget::edit::text_change(sge::gui::text_callback &&_callback)
{
  return text_change_.connect(std::move(_callback));
}

sge::rucksack::widget::base &sge::gui::widget::edit::layout() { return layout_; }

void sge::gui::widget::edit::on_update(sge::gui::duration const _duration)
{
  if (!has_focus_)
  {
    return;
  }

  clock_.update(_duration);

  if (sge::timer::reset_when_expired(fcppt::make_ref(cursor_blink_timer_)))
  {
    show_cursor_ = !show_cursor_;
  }
}

void sge::gui::widget::edit::on_draw(
    sge::gui::renderer::base &_renderer, sge::renderer::context::ffp &_context)
{
  // TODO(philipp): Add a signal to sge that tells us when a layout changes
  static_text_ = this->make_static_text();

  style_.get().draw_edit(_renderer, _context, this->layout().area());

  _renderer.draw_static_text(_context, static_text_);

  if (!has_focus_ || !show_cursor_)
  {
    return;
  }

  sge::font::rect const cursor_rect(static_text_.text().cursor_rect(position_));

  _renderer.fill_rect(
      _context,
      sge::rucksack::rect(
          cursor_rect.pos() + static_text_.pos(),
          sge::font::dim(
              // TODO(philipp): How do we specify the width?
              2,
              cursor_rect.size().h())),
      style_.get().text_color().get());
}

sge::gui::get_focus sge::gui::widget::edit::on_click(sge::rucksack::vector const &_pos)
{
  fcppt::optional::maybe(
      static_text_.text().pos_to_index(
          fcppt::math::vector::structure_cast<sge::font::vector, fcppt::cast::size_fun>(_pos) -
          static_text_.pos()),
      [_pos, this]
      {
        if (_pos.x() >= static_text_.rect().size().w() + static_text_.pos().x())
        {
          position_ = text_.size();
        }
      },
      [this](sge::font::index const _index)
      {
        if (_index > this->text_.size())
        {
          throw sge::gui::exception{FCPPT_TEXT("edit: Index out of range!")};
        }

        position_ = _index;
      });

  return sge::gui::get_focus(true);
}

void sge::gui::widget::edit::on_key(sge::input::key::code const _code)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

  switch (_code)
  {
  case sge::input::key::code::left:
    if (position_ != 0U)
    {
      --position_;
    }

    break;
  case sge::input::key::code::right:
    if (position_ < text_.size())
    {
      ++position_;
    }

    break;
  case sge::input::key::code::delete_:
    if (position_ != text_.size())
    {
      text_.erase(position_, 1U);

      this->text_changed();
    }

    break;
  case sge::input::key::code::backspace:
    if (position_ - 1U < text_.size())
    {
      text_.erase(position_ - 1U, 1U);

      --position_;

      this->text_changed();
    }

    break;
  default:
    break;
  }

  FCPPT_PP_POP_WARNING
}

void sge::gui::widget::edit::on_char(sge::font::char_type const _char)
{
  if (!std::isprint(_char, fcppt::string_conv_locale()))
  {
    return;
  }

  text_.insert(position_, 1U, _char);

  ++position_;

  this->text_changed();
}

void sge::gui::widget::edit::on_focus_changed(sge::gui::focus_change const _change)
{
  has_focus_ = _change == sge::gui::focus_change::gained;

  if (has_focus_)
  {
    show_cursor_ = true;

    cursor_blink_timer_.reset();
  }
}

sge::gui::widget::optional_ref sge::gui::widget::edit::on_tab(sge::gui::widget::optional_focus_ref)
{
  return sge::gui::widget::optional_ref(
      fcppt::reference_to_base<sge::gui::widget::base>(fcppt::make_ref(*this)));
}

sge::font::draw::static_text sge::gui::widget::edit::make_static_text()
{
  return sge::font::draw::static_text(
      renderer_,
      font_,
      text_,
      sge::font::text_parameters(sge::font::align_h::variant{sge::font::align_h::left(
                                     sge::font::align_h::max_width(std::max(
                                         layout_.size().w() - style_.get().edit_spacing().w(),
                                         fcppt::literal<sge::font::unit>(0))))})
          .flags(sge::font::flags_field{sge::font::flags::no_multi_line}),
      fcppt::math::vector::structure_cast<sge::font::vector, fcppt::cast::size_fun>(
          layout_.position() +
          fcppt::math::vector::fill<sge::rucksack::vector>(style_.get().edit_spacing().w() / 2)) +
          sge::font::vector(
              0,
              sge::font::v_center(
                  font_.get().metrics().height(),
                  layout_.size().h() - style_.get().edit_spacing().h())),
      style_.get().text_color().get(),
      sge::renderer::texture::emulate_srgb::no);
}

void sge::gui::widget::edit::text_changed()
{
  static_text_ = this->make_static_text();

  text_change_(this->text());
}
