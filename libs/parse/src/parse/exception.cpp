//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/parse/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("parse: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::parse::exception::exception(
	exception &&
)
= default;

sge::parse::exception::exception(
	exception const &
)
= default;

sge::parse::exception &
sge::parse::exception::operator=(
	exception &&
)
= default;

sge::parse::exception &
sge::parse::exception::operator=(
	exception const &
)
= default;

sge::parse::exception::~exception() noexcept
{
}
