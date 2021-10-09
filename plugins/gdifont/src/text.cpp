//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/dim.hpp>
#include <sge/font/exception.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view.hpp>
#include <sge/gdifont/a8_view.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/colors_to_max.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/dib_section.hpp>
#include <sge/gdifont/make_flags.hpp>
#include <sge/gdifont/render.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <sge/gdifont/set_bk_color.hpp>
#include <sge/gdifont/set_text_color.hpp>
#include <sge/gdifont/text.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/algorithm/copy.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::gdifont::text::text(
    sge::gdifont::device_context const &_device_context,
    HFONT const _hfont,
    sge::font::string const &_string,
    sge::font::text_parameters const &_text_parameters)
    : sge::font::text(),
      device_context_(_device_context),
      hfont_(_hfont),
      string_(_string),
      render_flags_(sge::gdifont::make_flags(_text_parameters)),
      rect_(sge::gdifont::calc_rect(
          device_context_, hfont_, string_, _text_parameters.align_h(), render_flags_))
{
}

sge::gdifont::text::~text() {}

void sge::gdifont::text::render(sge::font::view const &_view)
{
  if (!fcppt::variant::holds_type<sge::gdifont::a8_view>(_view.get()))
    throw sge::font::exception(FCPPT_TEXT("Only a8 formats are currently supported in gdifont!"));

  sge::image2d::dim const view_size(sge::image2d::view::size(_view));

  sge::gdifont::dib_section dib_section(device_context_, view_size);

  sge::gdifont::scoped_select const select_font(device_context_, hfont_);

  sge::gdifont::scoped_select const select_dib(device_context_, dib_section.handle());

  sge::gdifont::set_bk_color(device_context_, RGB(0, 0, 0));

  sge::gdifont::set_text_color(device_context_, RGB(255, 255, 255));

  sge::gdifont::render(device_context_, string_, rect_.size(), render_flags_);

  sge::gdifont::colors_to_max(dib_section.view());

  sge::image2d::algorithm::copy(
      dib_section.const_view(),
      _view,
      sge::image::algorithm::may_overlap::no,
      sge::image::algorithm::uninitialized::yes);
}

sge::font::rect sge::gdifont::text::rect() const { return rect_; }

sge::font::dim sge::gdifont::text::logical_size() const { return rect_.size(); }

sge::font::rect sge::gdifont::text::cursor_rect(sge::font::index const _index) const
{
  // FIXME
  return fcppt::math::box::null<sge::font::rect>();
}

sge::font::optional_index sge::gdifont::text::pos_to_index(sge::font::vector const _pos) const
{
  // FIXME
  return sge::font::optional_index();
}
