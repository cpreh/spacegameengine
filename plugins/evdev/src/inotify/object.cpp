//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/inotify/object.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unistd.h>
#include <sys/inotify.h>
#include <fcppt/config/external_end.hpp>

sge::evdev::inotify::object::object() : fd_(::inotify_init1(IN_CLOEXEC))
{
  if (fd_.get() == -1)
  {
    throw sge::input::exception(FCPPT_TEXT("inotify_init failed"));
  }
}

sge::evdev::inotify::object::~object() { ::close(fd_.get()); }

awl::backends::posix::fd sge::evdev::inotify::object::fd() { return fd_; }
