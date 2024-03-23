//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_BUTTON_CODE_HPP_INCLUDED
#define SGE_INPUT_MOUSE_BUTTON_CODE_HPP_INCLUDED

#include <sge/input/mouse/button_code_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::input::mouse
{

enum class button_code : std::uint8_t
{
  left,
  right,
  middle,
  unknown
};

}

#endif
