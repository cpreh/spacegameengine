//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("input: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::input::exception::exception(
	fcppt::assert_::information const &_info
)
:
	sge::core::exception(
		_info
	)
{
}

sge::input::exception::exception(
	exception &&
)
= default;

sge::input::exception::exception(
	exception const &
)
= default;

sge::input::exception &
sge::input::exception::operator=(
	exception &&
)
= default;

sge::input::exception &
sge::input::exception::operator=(
	exception const &
)
= default;

sge::input::exception::~exception() noexcept
{
}
