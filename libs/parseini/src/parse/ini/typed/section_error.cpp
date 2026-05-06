//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/typed/section_error.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/variant/comparison.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::typed::section_error::section_error(
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    sge::parse::ini::section_name &&_name, variant &&_variant)
    : name_{std::move(_name.get())}, variant_{std::move(_variant)}
{
}

bool sge::parse::ini::typed::section_error::operator==(
    sge::parse::ini::typed::section_error const &) const noexcept = default;
