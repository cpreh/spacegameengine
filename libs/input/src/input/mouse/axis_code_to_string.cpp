//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_code_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sge::input::mouse::axis_code_to_string(sge::input::mouse::axis_code const _code)
{
#define MAKE_CASE(name) \
  case sge::input::mouse::axis_code::name: \
    return FCPPT_TEXT(#name);

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_code)
  {
    MAKE_CASE(x)
    MAKE_CASE(y)
    MAKE_CASE(wheel)
    MAKE_CASE(unknown)
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_code);
}
