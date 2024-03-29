//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/libpng/format.hpp>
#include <sge/libpng/transforms_from_format.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <png.h>
#include <fcppt/config/external_end.hpp>

int sge::libpng::transforms_from_format(sge::libpng::format const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::libpng::format::l8:
  case sge::libpng::format::la8:
  case sge::libpng::format::srgb8:
  case sge::libpng::format::srgba8:
    return PNG_TRANSFORM_IDENTITY;
  case sge::libpng::format::sbgr8:
  case sge::libpng::format::sbgra8:
    return PNG_TRANSFORM_BGR;
    // TODO(philipp): Do we want srgbx/bgrx?
    //	PNG_TRANSFORM_STRIP_FILLER_AFTER;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
