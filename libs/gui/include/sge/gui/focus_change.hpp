//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_FOCUS_CHANGE_HPP_INCLUDED
#define SGE_GUI_FOCUS_CHANGE_HPP_INCLUDED

#include <sge/gui/focus_change_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::gui
{

enum class focus_change : std::uint8_t
{
  gained,
  lost
};

}

#endif
