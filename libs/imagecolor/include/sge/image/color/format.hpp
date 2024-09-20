//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

enum class format : std::uint8_t
{
  a8,
  l8,
  r32f,
  la8,
  rgb8,
  bgr8,
  rgba8,
  rgbx8,
  bgra8,
  bgrx8,
  rgb32f,
  bgr32f,
  rgba32f,
  bgra32f,
  srgb8,
  srgba8,
  sbgr8,
  sbgra8
};

FCPPT_PP_POP_WARNING

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::image::color::format::sbgra8);

#endif
