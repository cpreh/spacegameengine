//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sge::input::joypad::ff::type_to_string(sge::input::joypad::ff::type const _type)
{
#define SGE_FF_TYPE_TO_STRING_CASE(name) \
  case sge::input::joypad::ff::type::name: \
    return FCPPT_TEXT(#name)

  switch (_type)
  {
    SGE_FF_TYPE_TO_STRING_CASE(constant);
    SGE_FF_TYPE_TO_STRING_CASE(spring);
    SGE_FF_TYPE_TO_STRING_CASE(friction);
    SGE_FF_TYPE_TO_STRING_CASE(damper);
    SGE_FF_TYPE_TO_STRING_CASE(inertia);
    SGE_FF_TYPE_TO_STRING_CASE(ramp);
    SGE_FF_TYPE_TO_STRING_CASE(square);
    SGE_FF_TYPE_TO_STRING_CASE(sine);
    SGE_FF_TYPE_TO_STRING_CASE(saw_up);
    SGE_FF_TYPE_TO_STRING_CASE(saw_down);
    SGE_FF_TYPE_TO_STRING_CASE(custom);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
