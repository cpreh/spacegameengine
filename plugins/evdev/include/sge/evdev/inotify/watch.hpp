//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_INOTIFY_WATCH_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_WATCH_HPP_INCLUDED

#include <sge/evdev/inotify/object_ref.hpp>
#include <sge/evdev/inotify/watch_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::inotify
{

class watch
{
  FCPPT_NONMOVABLE(watch);

public:
  watch(std::filesystem::path const &, sge::evdev::inotify::object_ref);

  ~watch();

private:
  sge::evdev::inotify::object_ref const object_;

  awl::backends::posix::fd const fd_;
};

}

#endif
