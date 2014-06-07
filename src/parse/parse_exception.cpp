/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/error_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/parse_exception.hpp>
#include <sge/parse/result_code.hpp>


sge::parse::parse_exception::parse_exception(
	sge::parse::result_code const _result_code,
	sge::parse::error_string const &_error_string
)
:
	sge::parse::exception(
		_error_string.get()
	),
	result_code_(
		_result_code
	),
	error_string_(
		_error_string
	)
{
}

sge::parse::result_code
sge::parse::parse_exception::result_code() const
{
	return result_code_;
}

sge::parse::error_string const &
sge::parse::parse_exception::error_string() const
{
	return error_string_;
}

sge::parse::parse_exception::~parse_exception() throw()
{
}
