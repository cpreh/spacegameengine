//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::invalid_get::invalid_get(
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

sge::parse::json::invalid_get::invalid_get(
	invalid_get &&
)
noexcept
= default;

sge::parse::json::invalid_get::invalid_get(
	invalid_get const &
)
= default;

sge::parse::json::invalid_get &
sge::parse::json::invalid_get::operator=(
	invalid_get &&
)
noexcept
= default;

sge::parse::json::invalid_get &
sge::parse::json::invalid_get::operator=(
	invalid_get const &
)
= default;

sge::parse::json::invalid_get::~invalid_get()
noexcept
= default;
