//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/font/view.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/data.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <sge/pango/freetype/pixel_mode.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftbitmap.h>
#include <freetype/ftimage.h>
#include <fcppt/config/external_end.hpp>

FT_Bitmap sge::pango::freetype::make_bitmap(sge::font::view const &_view)
{
  sge::image2d::dim const size{sge::image2d::view::size(_view)};

  auto const width(fcppt::cast::size<unsigned>(size.w()));

  auto const height(fcppt::cast::size<unsigned>(size.h()));

  FT_Bitmap bitmap;

  FT_Bitmap_Init(&bitmap);

  bitmap.rows = height;

  bitmap.width = width;

  int const pitch(fcppt::cast::size<int>(sge::image2d::view::pitch(_view).w()));

  // For FreeType, pitch means the distance from the start of one line to
  // the start of the next line. If the pitch is positive, the image goes
  // downwards. Because mizuiro doesn't include the width in this case,
  // we have to add it. If the pitch is negative, mizuiro already
  // includes the width (as a negative component), so add it back.
  bitmap.pitch = pitch + fcppt::cast::to_signed(width);

  bitmap.buffer = sge::image2d::view::data(_view);

  bitmap.num_grays = 256; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

  sge::image::color::format const format{sge::image2d::view::format(_view)};

  bitmap.pixel_mode = fcppt::optional::to_exception(
      sge::pango::freetype::pixel_mode(format),
      [format]
      {
        return sge::font::exception{
            FCPPT_TEXT("Unsupported image format ") + sge::image::color::format_to_string(format)};
      });

  return bitmap;
}
