//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED

#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/enum/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::device
{

template <typename Enum>
sge::evdev::device::read_bits_result<Enum> read_bits(
    sge::evdev::device::fd &_fd, // NOLINT(google-runtime-references)
    unsigned const _type)
{
  using result_type = sge::evdev::device::read_bits_result<Enum>;

  using array_type = typename result_type::array_type;

  array_type result{fcppt::no_init{}};

  if (::ioctl( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
          _fd.get().get(),
          EVIOCGBIT( // NOLINT(hicpp-signed-bitwise)
              _type,
              fcppt::cast::size<unsigned>(fcppt::enum_::size<Enum>::value)),
          result.data()) == -1)
  {
    throw sge::input::exception{FCPPT_TEXT("ioctl reading device capabilities failed!")};
  }

  return result_type(result);
}

}

#endif
