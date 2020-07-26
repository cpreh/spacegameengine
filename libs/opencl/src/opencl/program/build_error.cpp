//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/exception.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sge::opencl::program::build_error::build_error(
	fcppt::string const &_message
)
:
	sge::opencl::exception(
		FCPPT_TEXT("Error building OpenCL program: ")
		+
		_message
	),
	message_(
		_message
	)
{
}

sge::opencl::program::build_error::build_error(
	build_error &&
)
noexcept
= default;

sge::opencl::program::build_error::build_error(
	build_error const &
)
= default;

sge::opencl::program::build_error &
sge::opencl::program::build_error::operator=(
	build_error &&
)
noexcept
= default;

sge::opencl::program::build_error &
sge::opencl::program::build_error::operator=(
	build_error const &
)
= default;

sge::opencl::program::build_error::~build_error()
noexcept
= default;

fcppt::string const &
sge::opencl::program::build_error::message() const
{
	return
		message_;
}
