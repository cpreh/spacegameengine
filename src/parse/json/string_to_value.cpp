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
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/string_to_value.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/format.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/istringstream.hpp>


sge::parse::json::value
sge::parse::json::string_to_value(
	fcppt::string const &_string
)
{
	fcppt::string const edited(
		(
			fcppt::format(
				FCPPT_TEXT("{ \"value\" : %s }")
			)
			%
			_string
		).str()
	);

	fcppt::io::istringstream stream(
		edited
	);

	sge::parse::json::start result;

	sge::parse::result const ret(
		sge::parse::json::parse_stream(
			stream,
			result
		)
	);

	if(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	)
		throw sge::parse::parse_exception(
			ret.result_code(),
			*ret.error_string()
		);

	return
		result.variant.get<
			sge::parse::json::object
		>().members.find(
			FCPPT_TEXT("value")
		)->second;
}
