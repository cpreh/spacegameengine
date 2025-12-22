//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/typed/unused_entries.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::typed::unused_entries::unused_entries(
// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    sge::parse::ini::section_name &&_section_name, std::set<std::string> &&_entries)
    : section_name{std::move(_section_name.get())}, entries{std::move(_entries)}
{
}

bool sge::parse::ini::typed::unused_entries::operator==(unused_entries const &) const noexcept =
    default;
