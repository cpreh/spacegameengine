//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/conversion_failed.hpp>
#include <sge/charconv/exception.hpp>
#include <fcppt/text.hpp>


sge::charconv::conversion_failed::conversion_failed()
:
	sge::charconv::exception(
		FCPPT_TEXT("Conversion failed!")
	)
{
}

sge::charconv::conversion_failed::conversion_failed(
	conversion_failed &&
)
noexcept
= default;

sge::charconv::conversion_failed::conversion_failed(
	conversion_failed const &
)
= default;

sge::charconv::conversion_failed &
sge::charconv::conversion_failed::operator=(
	conversion_failed &&
)
noexcept
= default;

sge::charconv::conversion_failed &
sge::charconv::conversion_failed::operator=(
	conversion_failed const &
)
= default;

sge::charconv::conversion_failed::~conversion_failed()
noexcept
= default;
