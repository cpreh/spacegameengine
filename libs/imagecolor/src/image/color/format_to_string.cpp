//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/preprocessor/stringize.hpp>

fcppt::string sge::image::color::format_to_string(sge::image::color::format const _format)
{
#define SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(fmt) \
  case sge::image::color::format::fmt: \
    return FCPPT_PP_STRINGIZE(fmt)

  switch (_format)
  {
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(a8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(l8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(r32f);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(la8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgb8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgr8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgba8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgbx8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgra8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgrx8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgb32f);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgr32f);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgba32f);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgra32f);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(srgb8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(srgba8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(sbgr8);
    SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(sbgra8);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
