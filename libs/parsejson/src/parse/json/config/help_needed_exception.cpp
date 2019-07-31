//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/config/help_needed_exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::config::help_needed_exception::help_needed_exception(
	fcppt::string &&_string
)
:
	sge::parse::json::exception(
		std::move(
			_string
		)
	)
{
}

sge::parse::json::config::help_needed_exception::help_needed_exception(
	help_needed_exception &&
)
= default;

sge::parse::json::config::help_needed_exception::help_needed_exception(
	help_needed_exception const &
)
= default;

sge::parse::json::config::help_needed_exception &
sge::parse::json::config::help_needed_exception::operator=(
	help_needed_exception &&
)
= default;

sge::parse::json::config::help_needed_exception &
sge::parse::json::config::help_needed_exception::operator=(
	help_needed_exception const &
)
= default;

sge::parse::json::config::help_needed_exception::~help_needed_exception() noexcept
{
}
