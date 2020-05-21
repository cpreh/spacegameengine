//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("renderer: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::renderer::exception::exception(
	fcppt::assert_::information const &_information
)
:
	sge::core::exception(
		_information
	)
{
}

sge::renderer::exception::exception(
	exception &&
)
noexcept
= default;

sge::renderer::exception::exception(
	exception const &
)
= default;

sge::renderer::exception &
sge::renderer::exception::operator=(
	exception &&
)
noexcept
= default;

sge::renderer::exception &
sge::renderer::exception::operator=(
	exception const &
)
= default;

sge::renderer::exception::~exception()
noexcept
= default;
