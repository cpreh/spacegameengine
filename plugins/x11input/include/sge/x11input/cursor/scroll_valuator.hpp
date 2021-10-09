//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_CURSOR_SCROLL_VALUATOR_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_SCROLL_VALUATOR_HPP_INCLUDED

#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/x11input/cursor/scroll_valuator_fwd.hpp>
#include <sge/x11input/device/valuator/any.hpp>
#include <sge/x11input/device/valuator/value.hpp>

namespace sge::x11input::cursor
{

class scroll_valuator
{
public:
  scroll_valuator(sge::x11input::device::valuator::any const &, sge::input::cursor::scroll_code);

  [[nodiscard]] sge::input::cursor::scroll_code code() const;

  [[nodiscard]] sge::input::cursor::scroll_value update(sge::x11input::device::valuator::value);

private:
  sge::x11input::device::valuator::any any_;

  sge::input::cursor::scroll_code code_;
};

}

#endif
