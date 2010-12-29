/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/parse/json/make_error_message.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sge::parse::json::make_error_message(
	json::string const &_first_part,
	json::string const &_second_part,
	json::string const &_expected
)
{
	json::string::size_type line_number(
		1u
	);

	json::string::size_type line_begin(
		0u
	);

	{
		json::string::size_type index(
			0u
		);

		for(
			;;
		)
		{
			index =
				_first_part.find(
					SGE_PARSE_JSON_TEXT('\n'),
					index
				);
			if(
				index == json::string::npos
			)
				break;

			++line_number;

			line_begin = index;
		}
	}

	// TODO: use conversions!
	fcppt::string ret(
		_first_part.empty()
		?
			fcppt::string(
				FCPPT_TEXT("")
			)
		:
			_first_part.substr(
				line_begin
			)
	);

	json::string::size_type const error_column(
		ret.size()
	);

	ret +=
		_second_part.substr(
			0u,
			_second_part.find(
				SGE_PARSE_JSON_TEXT('\n')
			)
		)
		+ FCPPT_TEXT('\n');

	ret.append(
		error_column,
		FCPPT_TEXT(' ')
	);

	ret.push_back(
		FCPPT_TEXT('^')
	);

	return
		FCPPT_TEXT("Expected ")
		+ _expected
		+ FCPPT_TEXT(" on line ")
		+ fcppt::lexical_cast<
			fcppt::string
		>(
			line_number
		)
		+ FCPPT_TEXT('\n')
		+ ret;
}
