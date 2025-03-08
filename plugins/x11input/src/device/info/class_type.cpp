//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/device/info/class_type.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <cstring>
#include <fcppt/config/external_end.hpp>

int sge::x11input::device::info::class_type(XIAnyClassInfo const &_info)
{
  // don't dereference _info because that's not its actual type!
  int ret{};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(&ret, fcppt::cast::to_char_ptr<unsigned char const *>(&_info), sizeof(int));
FCPPT_PP_POP_WARNING

  return ret;
}
