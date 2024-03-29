//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/from_sge_format.hpp>
#include <sge/libpng/optional_format.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::libpng::optional_format sge::libpng::from_sge_format(sge::image::color::format const _format)
{
#define SGE_LIBPNG_CONVERT_FORMAT(cur_format) \
  case sge::image::color::format::cur_format: \
    return sge::libpng::optional_format { sge::libpng::format::cur_format }

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
    SGE_LIBPNG_CONVERT_FORMAT(l8);
    SGE_LIBPNG_CONVERT_FORMAT(la8);
  case sge::image::color::format::rgb8:
    return sge::libpng::optional_format{sge::libpng::format::srgb8};
  case sge::image::color::format::bgr8:
    return sge::libpng::optional_format{sge::libpng::format::sbgr8};
  case sge::image::color::format::rgba8:
  case sge::image::color::format::rgbx8:
    return sge::libpng::optional_format{sge::libpng::format::srgba8};
  case sge::image::color::format::bgra8:
  case sge::image::color::format::bgrx8:
    return sge::libpng::optional_format{sge::libpng::format::sbgra8};
    SGE_LIBPNG_CONVERT_FORMAT(srgb8);
    SGE_LIBPNG_CONVERT_FORMAT(srgba8);
    SGE_LIBPNG_CONVERT_FORMAT(sbgr8);
    SGE_LIBPNG_CONVERT_FORMAT(sbgra8);
  case sge::image::color::format::a8:
  case sge::image::color::format::r32f:
  case sge::image::color::format::rgb32f:
  case sge::image::color::format::bgr32f:
  case sge::image::color::format::rgba32f:
  case sge::image::color::format::bgra32f:
    return sge::libpng::optional_format{};
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
