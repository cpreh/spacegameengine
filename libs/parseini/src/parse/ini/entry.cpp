//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
sge::parse::ini::entry::entry(sge::parse::ini::entry_name &&_name, sge::parse::ini::value &&_value)
    : name{std::move(_name.get())}, value{std::move(_value.get())}
{
}

bool sge::parse::ini::operator==(
    sge::parse::ini::entry const &_left, sge::parse::ini::entry const &_right)
{
  return _left.name == _right.name && _left.value == _right.value;
}
