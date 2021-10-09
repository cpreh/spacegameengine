//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/exception.hpp>
#include <sge/systems/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::exception::exception(fcppt::string &&_what)
    : sge::core::exception(FCPPT_TEXT("systems: ") + std::move(_what))
{
}

sge::systems::exception::exception(exception &&) noexcept = default;

sge::systems::exception::exception(exception const &) = default;

sge::systems::exception &sge::systems::exception::operator=(exception &&) noexcept = default;

sge::systems::exception &sge::systems::exception::operator=(exception const &) = default;

sge::systems::exception::~exception() noexcept = default;
