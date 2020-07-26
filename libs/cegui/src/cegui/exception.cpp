//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/exception.hpp>
#include <sge/core/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cegui::exception::exception(
	fcppt::string &&_string
)
:
	sge::core::exception(
		FCPPT_TEXT("cegui: ")
		+
		std::move(
			_string
		)
	)
{
}

sge::cegui::exception::exception(
	exception &&
)
noexcept
= default;

sge::cegui::exception::exception(
	exception const &
)
= default;

sge::cegui::exception &
sge::cegui::exception::operator=(
	exception &&
)
noexcept
= default;

sge::cegui::exception &
sge::cegui::exception::operator=(
	exception const &
)
= default;

sge::cegui::exception::~exception()
noexcept
= default;
