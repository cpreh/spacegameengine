//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/typed/entry_error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::typed::entry_error::entry_error(
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    std::type_index &&_type, sge::parse::ini::entry_name &&_name, sge::parse::ini::value &&_value)
    : type{_type}, name{std::move(_name.get())}, value{std::move(_value.get())}
{
}

bool sge::parse::ini::typed::entry_error::operator==(
    sge::parse::ini::typed::entry_error const &) const noexcept = default;
