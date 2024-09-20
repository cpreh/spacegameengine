//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_COLOR_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_COLOR_FORMAT_HPP_INCLUDED

#include <sge/opengl/color_format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl
{

enum class color_format : std::uint8_t
{
  a8,
  l8,
  r32f,
  la8,
  rgb8,
  bgr8,
  rgba8,
  bgra8,
  rgb32f,
  bgr32f,
  rgba32f,
  bgra32f,
  srgb8,
  srgba8,
  sbgr8,
  sbgra8
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::opengl::color_format::sbgra8);

#endif
