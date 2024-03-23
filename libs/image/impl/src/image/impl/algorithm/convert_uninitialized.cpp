//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

mizuiro::image::algorithm::uninitialized sge::image::impl::algorithm::convert_uninitialized(
    sge::image::algorithm::uninitialized const _uninitialized)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_uninitialized)
  {
  case sge::image::algorithm::uninitialized::no:
    return mizuiro::image::algorithm::uninitialized::no;
  case sge::image::algorithm::uninitialized::yes:
    return mizuiro::image::algorithm::uninitialized::yes;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_uninitialized);
}
