//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sge::input::capabilities_to_string(sge::input::capabilities const _capabilities)
{
#define SGE_INPUT_CAPABILITIES_TO_STRING_CASE(name) \
  case sge::input::capabilities::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_capabilities)
  {
    SGE_INPUT_CAPABILITIES_TO_STRING_CASE(cursor);
    SGE_INPUT_CAPABILITIES_TO_STRING_CASE(focus);
    SGE_INPUT_CAPABILITIES_TO_STRING_CASE(keyboard);
    SGE_INPUT_CAPABILITIES_TO_STRING_CASE(joypad);
    SGE_INPUT_CAPABILITIES_TO_STRING_CASE(mouse);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_capabilities);
}
