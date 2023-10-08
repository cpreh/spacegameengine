//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/pango/create_font_map.hpp>
#include <sge/pango/create_layout.hpp>
#include <sge/pango/make_metrics.hpp>
#include <sge/pango/object.hpp>
#include <sge/pango/text.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-fontmap.h>
#include <fcppt/config/external_end.hpp>

sge::pango::object::object(sge::font::parameters const &_parameters)
    : sge::font::object(),
      font_map_(sge::pango::create_font_map(_parameters)),
      context_(::pango_font_map_create_context(font_map_.get_pointer())),
      layout_(sge::pango::create_layout(fcppt::make_ref(*context_), _parameters)),
      metrics_(sge::pango::make_metrics(*layout_))
{
}

sge::pango::object::~object() = default;

sge::font::text_unique_ptr sge::pango::object::create_text(
    sge::font::string const &_text, sge::font::text_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::font::text>(fcppt::make_unique_ptr<sge::pango::text>(
      *layout_,
      sge::charconv::convert<sge::charconv::encoding::utf8, sge::charconv::encoding::wchar>(_text),
      _parameters));
}

sge::image::color::optional_format sge::pango::object::preferred_color_format() const
{
  // TODO(philipp): This should be extended to all formats
  return sge::image::color::optional_format(sge::image::color::format::a8);
}

sge::font::metrics sge::pango::object::metrics() const { return metrics_; }
