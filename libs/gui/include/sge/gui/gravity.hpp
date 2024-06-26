//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_GRAVITY_HPP_INCLUDED
#define SGE_GUI_GRAVITY_HPP_INCLUDED

#include <sge/gui/gravity_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::gui
{

enum class gravity : std::uint8_t
{
  north_west,
  south_west,
  south_east,
  north_east
};

}

#endif
