//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/shader/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::shader::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception{
		FCPPT_TEXT("shader: ")
		+
		std::move(
			_what
		)
	}
{
}

sge::shader::exception::exception(
	exception &&
)
noexcept
= default;

sge::shader::exception::exception(
	exception const &
)
= default;

sge::shader::exception &
sge::shader::exception::operator=(
	exception &&
)
noexcept
= default;

sge::shader::exception &
sge::shader::exception::operator=(
	exception const &
)
= default;

sge::shader::exception::~exception()
noexcept
= default;
