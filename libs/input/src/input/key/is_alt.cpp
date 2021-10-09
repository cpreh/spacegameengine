//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/key/code.hpp>
#include <sge/input/key/is_alt.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

bool sge::input::key::is_alt(sge::input::key::code const _key)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

  switch (_key)
  {
  case sge::input::key::code::left_alt:
  case sge::input::key::code::right_alt:
    return true;
  default:
    return false;
  }

  FCPPT_PP_POP_WARNING
}
