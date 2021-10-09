//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_FOCUS_LOOKED_UP_STRING_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_LOOKED_UP_STRING_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge::x11input::focus
{

class looked_up_string
{
  FCPPT_NONCOPYABLE(looked_up_string);

public:
  looked_up_string(sge::x11input::focus::char_vector &&, sge::input::key::code) noexcept;

  looked_up_string(looked_up_string &&) noexcept;

  looked_up_string &operator=(looked_up_string &&) noexcept;

  ~looked_up_string() noexcept;

  [[nodiscard]] sge::x11input::focus::char_vector const &char_codes() const noexcept;

  [[nodiscard]] sge::input::key::code key_code() const noexcept;

private:
  sge::x11input::focus::char_vector char_codes_;

  sge::input::key::code key_code_;
};

}

#endif
