//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/exception.hpp>
#include <sge/core/exception.hpp>
#include <sge/font/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::console::exception::exception(
	sge::font::string &&_console_string
)
:
	sge::core::exception(
		FCPPT_TEXT("console error")
	),
	console_string_(
		std::move(
			_console_string
		)
	)
{
}

sge::console::exception::exception(
	exception &&
)
= default;

sge::console::exception::exception(
	exception const &
)
= default;

sge::console::exception &
sge::console::exception::operator=(
	exception &&
)
= default;

sge::console::exception &
sge::console::exception::operator=(
	exception const &
)
= default;

sge::console::exception::~exception() noexcept
{
}

sge::font::string const &
sge::console::exception::console_string() const
{
	return
		console_string_;
}
