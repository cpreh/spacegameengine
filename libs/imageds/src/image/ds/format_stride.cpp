//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/channel16.hpp>
#include <sge/image/channel32.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/ds/format.hpp>
#include <sge/image/ds/format_stride.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::image::size_type sge::image::ds::format_stride(sge::image::ds::format const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::image::ds::format::d16:
    return sizeof(sge::image::channel16);
  case sge::image::ds::format::d32:
  case sge::image::ds::format::d24s8:
    return sizeof(sge::image::channel32);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
