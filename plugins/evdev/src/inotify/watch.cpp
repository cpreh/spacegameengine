//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/inotify/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/evdev/inotify/object_ref.hpp>
#include <sge/evdev/inotify/watch.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/inotify.h>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::evdev::inotify::watch::watch(
    std::filesystem::path const &_watch_path, sge::evdev::inotify::object_ref const _object)
    : object_(_object),
      fd_(::inotify_add_watch(
          object_.get().fd().get(),
          _watch_path.string().c_str(),
          IN_CREATE // NOLINT(hicpp-signed-bitwise)
              | IN_DELETE | IN_ATTRIB))
{
  if (fd_.get() == -1)
  {
    throw sge::input::exception(FCPPT_TEXT("inotify_add_watch failed"));
  }
}

sge::evdev::inotify::watch::~watch() { ::inotify_rm_watch(object_.get().fd().get(), fd_.get()); }
