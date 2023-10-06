//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/fd.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::evdev::device::fd::fd(std::filesystem::path const &_path)
    : fd_(::open( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
          _path.string().c_str(),
          O_RDONLY | O_NONBLOCK | O_CLOEXEC // NOLINT(hicpp-signed-bitwise)
          ))
{
}

sge::evdev::device::fd::~fd()
{
  if (this->valid())
  {
    ::close(this->fd_.get());
  }
}

awl::backends::posix::fd sge::evdev::device::fd::get()
{
  if (!this->valid())
  {
    throw sge::input::exception{FCPPT_TEXT("evdev: Invalid fd.")};
  }

  return this->fd_;
}

bool sge::evdev::device::fd::valid() const { return this->fd_.get() != -1; }
