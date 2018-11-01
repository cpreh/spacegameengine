/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
= default;

sge::opencl::program::build_error::build_error(
	build_error const &
)
= default;

sge::opencl::program::build_error &
sge::opencl::program::build_error::operator=(
	build_error &&
)
= default;

sge::opencl::program::build_error &
sge::opencl::program::build_error::operator=(
	build_error const &
)
= default;

sge::opencl::program::build_error::~build_error() noexcept
{
}

fcppt::string const &
sge::opencl::program::build_error::message() const
{
	return
		message_;
}
