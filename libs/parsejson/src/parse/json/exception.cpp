//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/exception.hpp>
#include <sge/parse/json/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::json::exception::exception(fcppt::string &&_what)
    : sge::parse::exception(FCPPT_TEXT("json: ") + std::move(_what))
{
}

sge::parse::json::exception::exception(exception &&) noexcept = default;

sge::parse::json::exception::exception(exception const &) = default;

sge::parse::json::exception &
sge::parse::json::exception::operator=(exception &&) noexcept = default;

sge::parse::json::exception &sge::parse::json::exception::operator=(exception const &) = default;

sge::parse::json::exception::~exception() noexcept = default;
