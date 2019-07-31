//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/model/md3/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::model::md3::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("md3: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::model::md3::exception::exception(
	exception &&
)
= default;

sge::model::md3::exception::exception(
	exception const &
)
= default;

sge::model::md3::exception &
sge::model::md3::exception::operator=(
	exception &&
)
= default;

sge::model::md3::exception &
sge::model::md3::exception::operator=(
	exception const &
)
= default;

sge::model::md3::exception::~exception() noexcept
{
}
