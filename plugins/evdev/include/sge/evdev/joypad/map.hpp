//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_MAP_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_MAP_HPP_INCLUDED

#include <sge/evdev/joypad/shared_ptr.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_std_hash.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::joypad
{

using map = std::unordered_map<awl::backends::posix::fd, sge::evdev::joypad::shared_ptr>;

}

#endif
