//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/opencl/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opencl::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("opencl: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::opencl::exception::exception(
	fcppt::assert_::information const &_information
)
:
	sge::core::exception(
		_information
	)
{
}

sge::opencl::exception::exception(
	exception &&
)
= default;

sge::opencl::exception::exception(
	exception const &
)
= default;

sge::opencl::exception &
sge::opencl::exception::operator=(
	exception &&
)
= default;

sge::opencl::exception &
sge::opencl::exception::operator=(
	exception const &
)
= default;

sge::opencl::exception::~exception() noexcept
{
}
