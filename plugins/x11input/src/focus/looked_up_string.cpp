//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/key/code.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::x11input::focus::looked_up_string::looked_up_string(
    sge::x11input::focus::char_vector &&_char_codes, sge::input::key::code const _key_code) noexcept
    : char_codes_(std::move(_char_codes)), key_code_(_key_code)
{
}

sge::x11input::focus::looked_up_string::looked_up_string(looked_up_string &&) noexcept = default;

sge::x11input::focus::looked_up_string &
sge::x11input::focus::looked_up_string::operator=(looked_up_string &&) noexcept = default;

sge::x11input::focus::looked_up_string::~looked_up_string() noexcept = default;

sge::x11input::focus::char_vector const &
sge::x11input::focus::looked_up_string::char_codes() const noexcept
{
  return char_codes_;
}

sge::input::key::code sge::x11input::focus::looked_up_string::key_code() const noexcept
{
  return key_code_;
}
