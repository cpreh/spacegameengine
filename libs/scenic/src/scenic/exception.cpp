//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/scenic/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception{
		FCPPT_TEXT("scenic: ")
		+
		std::move(
			_what
		)
	}
{
}

sge::scenic::exception::exception(
	exception &&
)
= default;

sge::scenic::exception::exception(
	exception const &
)
= default;

sge::scenic::exception &
sge::scenic::exception::operator=(
	exception &&
)
= default;

sge::scenic::exception &
sge::scenic::exception::operator=(
	exception const &
)
= default;

sge::scenic::exception::~exception() noexcept
{
}
