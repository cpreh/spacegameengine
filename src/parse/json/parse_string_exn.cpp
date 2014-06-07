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


#include <sge/parse/parse_exception.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/json/parse_range.hpp>
#include <sge/parse/json/parse_string_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/string.hpp>


sge::parse::json::start
sge::parse::json::parse_string_exn(
	fcppt::string const &_string
)
{
	sge::parse::json::start result;

	fcppt::string::const_iterator current(
		_string.begin()
	);

	sge::parse::result const ret(
		sge::parse::json::parse_range(
			current,
			_string.end(),
			result
		)
	);

	if(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	)
		throw
			sge::parse::parse_exception(
				ret.result_code(),
				*ret.error_string()
			);

	return result;
}
