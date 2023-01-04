//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::core::exception::exception(fcppt::string &&_string) : fcppt::exception(std::move(_string)) {}

sge::core::exception::exception(exception &&) noexcept = default;

sge::core::exception::exception(exception const &) = default;

sge::core::exception &sge::core::exception::operator=(exception &&) noexcept = default;

sge::core::exception &sge::core::exception::operator=(exception const &) = default;

sge::core::exception::~exception() noexcept = default;
