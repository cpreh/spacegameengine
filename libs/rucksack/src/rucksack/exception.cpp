//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/exception.hpp>
#include <sge/rucksack/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::rucksack::exception::exception(fcppt::string &&_what)
    : sge::core::exception(FCPPT_TEXT("rucksack: ") + std::move(_what))
{
}

sge::rucksack::exception::exception(exception &&) noexcept = default;

sge::rucksack::exception::exception(exception const &) = default;

sge::rucksack::exception &sge::rucksack::exception::operator=(exception &&) noexcept = default;

sge::rucksack::exception &sge::rucksack::exception::operator=(exception const &) = default;

sge::rucksack::exception::~exception() noexcept = default;
