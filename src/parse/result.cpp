/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>


sge::parse::result::result(
	sge::parse::result_code const _result_code,
	sge::parse::optional_error_string const &_error_string
)
:
	result_code_(
		_result_code
	),
	error_string_(
		_error_string
	)
{
}

sge::parse::result_code
sge::parse::result::result_code() const
{
	return result_code_;
}

sge::parse::optional_error_string const &
sge::parse::result::error_string() const
{
	return error_string_;
}
