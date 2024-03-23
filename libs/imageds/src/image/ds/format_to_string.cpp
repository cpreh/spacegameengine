//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/image/ds/format_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/preprocessor/stringize.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sge::image::ds::format_to_string(sge::image::ds::format const _format)
{
#define SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(fmt) \
  case sge::image::ds::format::fmt: \
    return FCPPT_PP_STRINGIZE(fmt)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
    SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d16);
    SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d32);
    SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d24s8);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
