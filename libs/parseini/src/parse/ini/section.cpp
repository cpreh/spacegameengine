//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::section::section(sge::parse::ini::section_name &&_name)
    : name{std::move(_name.get())}, entries{}
{
}

sge::parse::ini::section::section(
    sge::parse::ini::section_name &&_name, sge::parse::ini::entry_vector &&_entries)
    : name{std::move(_name.get())}, entries{std::move(_entries)}
{
}

bool sge::parse::ini::operator==(
    sge::parse::ini::section const &_left, sge::parse::ini::section const &_right)
{
  return _left.name == _right.name && _left.entries == _right.entries;
}
