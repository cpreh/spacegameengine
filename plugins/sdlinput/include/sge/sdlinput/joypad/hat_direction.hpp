//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_JOYPAD_HAT_DIRECTION_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_HAT_DIRECTION_HPP_INCLUDED

#include <sge/sdlinput/joypad/hat_direction_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::joypad
{

enum class hat_direction : std::uint8_t
{
  x,
  y
};

}

#endif
