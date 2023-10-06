//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/object.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/posix/processor.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/posix/processor_ref.hpp>
#include <awl/event/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/connection.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unistd.h>
#include <linux/input.h>
#include <sys/types.h>
#include <cerrno>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::evdev::device::object::object(
    sge::evdev::device::fd_unique_ptr &&_fd,
    awl::backends::posix::processor_ref const _processor,
    std::filesystem::path &&_path)
    : fd_{std::move(_fd)},
      fd_connection_{_processor.get().register_fd(this->fd_->get())},
      path_{std::move(_path)}
{
}

sge::evdev::device::object::~object() = default;

awl::event::container sge::evdev::device::object::on_event()
{
  ssize_t result{-1};

  input_event event{};

  awl::event::container events{};

  while ((result = ::read(fd_->get().get(), &event, sizeof(event))) > 0)
  {
    fcppt::optional::maybe_void(
        this->process_event(sge::evdev::device::event(event)),
        [&events](awl::event::base_unique_ptr &&_event) { events.push_back(std::move(_event)); });
  }

  if (result == -1 && errno != EAGAIN)
  {
    throw sge::input::exception{FCPPT_TEXT("Reading a device failed")};
  }

  return events;
}

awl::backends::posix::fd sge::evdev::device::object::posix_fd() { return this->fd().get(); }

std::filesystem::path const &sge::evdev::device::object::path() const { return path_; }

sge::evdev::device::fd &sge::evdev::device::object::fd() { return *fd_; }
