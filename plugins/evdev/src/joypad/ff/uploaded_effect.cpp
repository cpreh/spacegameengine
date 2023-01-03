//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_ref.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <sge/evdev/joypad/ff/uploaded_effect.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <exception>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::ff::uploaded_effect::uploaded_effect(
    sge::evdev::device::fd_ref const _fd, ff_effect const _effect)
    : fd_{_fd}, effect_{_effect}
{
  effect_.id = -1;

  if (::ioctl( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
          this->fd_.get().get().get(),
          EVIOCSFF, // NOLINT(hicpp-signed-bitwise)
          &this->effect_) == -1)
  {
    throw sge::input::exception{FCPPT_TEXT("Uploading a FF effect failed")};
  }
}

sge::evdev::joypad::ff::uploaded_effect::~uploaded_effect()
{
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  if (::ioctl( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
          this->fd_.get().get().get(),
          EVIOCRMFF,
          &this->effect_) == -1)
  {
    std::terminate();
  }
}

sge::evdev::joypad::ff::id sge::evdev::joypad::ff::uploaded_effect::id() const
{
  return sge::evdev::joypad::ff::id{this->effect_.id};
}
