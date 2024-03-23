//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/impl/algorithm/convert_may_overlap.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

mizuiro::image::algorithm::may_overlap sge::image::impl::algorithm::convert_may_overlap(
    sge::image::algorithm::may_overlap const _may_overlap)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_may_overlap)
  {
  case sge::image::algorithm::may_overlap::no:
    return mizuiro::image::algorithm::may_overlap::no;
  case sge::image::algorithm::may_overlap::yes:
    return mizuiro::image::algorithm::may_overlap::yes;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_may_overlap);
}
