/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/process/output.hpp>

sge::process::output::output(
	fcppt::string const &_output_stream,
	fcppt::string const &_error_stream,
	sge::process::exit_code const _exit_code)
:
	output_stream_(
		_output_stream),
	error_stream_(
		_error_stream),
	exit_code_(
		_exit_code)
{
}

fcppt::string const &
sge::process::output::output_stream() const
{
	return output_stream_;
}

fcppt::string const &
sge::process::output::error_stream() const
{
	return error_stream_;
}

sge::process::exit_code
sge::process::output::exit_code() const
{
	return exit_code_;
}
