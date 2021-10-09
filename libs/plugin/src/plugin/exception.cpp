//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/exception.hpp>
#include <sge/plugin/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::plugin::exception::exception(fcppt::string &&_error)
    : sge::core::exception(FCPPT_TEXT("plugin: ") + std::move(_error))
{
}

sge::plugin::exception::exception(exception &&) noexcept = default;

sge::plugin::exception::exception(exception const &) = default;

sge::plugin::exception &sge::plugin::exception::operator=(exception &&) noexcept = default;

sge::plugin::exception &sge::plugin::exception::operator=(exception const &) = default;

sge::plugin::exception::~exception() noexcept = default;
