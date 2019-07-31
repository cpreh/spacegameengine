//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/resource_tree/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("resource_tree: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::resource_tree::exception::exception(
	fcppt::assert_::information const &_info
)
:
	sge::core::exception(
		_info
	)
{
}

sge::resource_tree::exception::exception(
	exception &&
)
= default;

sge::resource_tree::exception::exception(
	exception const &
)
= default;

sge::resource_tree::exception &
sge::resource_tree::exception::operator=(
	exception &&
)
= default;

sge::resource_tree::exception &
sge::resource_tree::exception::operator=(
	exception const &
)
= default;

sge::resource_tree::exception::~exception() noexcept
{
}
