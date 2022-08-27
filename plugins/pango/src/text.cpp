//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/index.hpp>
#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_indices.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/optional_rect.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/clear.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/get_extents.hpp>
#include <sge/pango/get_strong_cursor_pos.hpp>
#include <sge/pango/index.hpp>
#include <sge/pango/text.hpp>
#include <sge/pango/xy_to_index.hpp>
#include <sge/pango/convert/from_rect_scale.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/algorithm/binary_search.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pangoft2.h>
#include <iterator>
#include <fcppt/config/external_end.hpp>

sge::pango::text::text(
    PangoLayout &_layout,
    sge::charconv::utf8_string const &_string,
    sge::font::text_parameters const &_text_parameters)
    : layout_(sge::pango::create_text_layout(_layout, _string, _text_parameters)),
      extents_(sge::pango::get_extents(*layout_)),
      indices_(sge::charconv::utf8_indices(_string))
{
}

sge::pango::text::~text() = default;

void sge::pango::text::render(sge::font::view const &_view)
{
  FT_Bitmap bitmap(sge::pango::freetype::make_bitmap(_view));

  sge::image2d::algorithm::fill(
      _view,
      sge::image::color::any::clear(sge::image2d::view::format(_view)),
      sge::image::algorithm::uninitialized::yes);

  ::pango_ft2_render_layout(
      &bitmap,
      layout_.get_pointer(),
      fcppt::cast::size<int>(-extents_.ink_rect().get().left()),
      fcppt::cast::size<int>(-extents_.ink_rect().get().top()));
}

sge::font::rect sge::pango::text::rect() const { return extents_.ink_rect().get(); }

sge::font::dim sge::pango::text::logical_size() const
{
  return extents_.logical_rect().get().size();
}

sge::font::optional_rect sge::pango::text::cursor_rect(sge::font::index const _index) const
{
  return fcppt::optional::map(
      fcppt::container::at_optional(this->indices_, _index),
      [this](fcppt::reference<sge::charconv::index const> const _pos) -> sge::font::rect
      {
        return sge::pango::convert::from_rect_scale(sge::pango::get_strong_cursor_pos(
            *this->layout_, fcppt::cast::size<int>(fcppt::cast::to_signed(_pos.get()))));
      });
}

sge::font::optional_index sge::pango::text::pos_to_index(sge::font::vector const _pos) const
{
  return fcppt::optional::bind(
      sge::pango::xy_to_index(*layout_, _pos),
      [this](sge::pango::index const _index)
      {
        return fcppt::optional::map(
            fcppt::algorithm::binary_search(
                indices_,
                fcppt::cast::size<sge::charconv::index>(
                    fcppt::cast::to_unsigned(_index.trailing().get() + _index.result().get()))),
            [this](sge::charconv::index_vector::const_iterator const _it)
            {
              return fcppt::cast::size<sge::font::index>(
                  fcppt::cast::to_unsigned(std::distance(indices_.begin(), _it)));
            });
      });
}
