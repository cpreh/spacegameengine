//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/size_type.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::image::size_type sge::image::color::element_count(sge::image::color::format const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::image::color::format::a8:
  case sge::image::color::format::l8:
  case sge::image::color::format::r32f:
    return 1;
  case sge::image::color::format::la8:
    return 2;
  case sge::image::color::format::rgb8:
  case sge::image::color::format::bgr8:
  case sge::image::color::format::rgb32f:
  case sge::image::color::format::bgr32f:
  case sge::image::color::format::srgb8:
  case sge::image::color::format::sbgr8:
    return 3;
  case sge::image::color::format::rgba8:
  case sge::image::color::format::rgbx8:
  case sge::image::color::format::bgra8:
  case sge::image::color::format::bgrx8:
  case sge::image::color::format::rgba32f:
  case sge::image::color::format::bgra32f:
  case sge::image::color::format::srgba8:
  case sge::image::color::format::sbgra8:
    return 4;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
