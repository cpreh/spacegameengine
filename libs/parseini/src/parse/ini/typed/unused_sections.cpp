//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/typed/unused_sections.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::typed::unused_sections::unused_sections(std::set<std::string> &&_sections)
    : sections{std::move(_sections)}
{
}

bool sge::parse::ini::typed::unused_sections::operator==(unused_sections const &) const noexcept =
    default;
