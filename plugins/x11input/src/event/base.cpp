//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/event/base.hpp>
#include <awl/backends/x11/system/event/generic.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <cstring>
#include <fcppt/config/external_end.hpp>

XIEvent sge::x11input::event::base(awl::backends::x11::system::event::generic const &_event)
{
  // Copy the head of the event to avoid strict-aliasing problems
  XIEvent result;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(&result, _event.data(), sizeof(XIEvent));
FCPPT_PP_POP_WARNING

  return result;
}
