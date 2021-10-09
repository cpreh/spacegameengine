//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::start::start(sge::parse::ini::section_vector &&_sections)
    : sections{std::move(_sections)}
{
}

bool sge::parse::ini::operator==(
    sge::parse::ini::start const &_left, sge::parse::ini::start const &_right)
{
  return _left.sections == _right.sections;
}
