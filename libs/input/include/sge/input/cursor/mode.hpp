//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_CURSOR_MODE_HPP_INCLUDED
#define SGE_INPUT_CURSOR_MODE_HPP_INCLUDED

#include <sge/input/cursor/mode_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::input::cursor
{

enum class mode : std::uint8_t
{
  exclusive,
  normal
};

}

#endif
