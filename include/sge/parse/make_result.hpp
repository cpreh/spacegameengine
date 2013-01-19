/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_MAKE_RESULT_HPP_INCLUDED
#define SGE_PARSE_MAKE_RESULT_HPP_INCLUDED

#include <sge/parse/error_string.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


namespace sge
{
namespace parse
{

template<
	typename In,
	typename Grammar
>
sge::parse::result const
make_result(
	bool const _retval,
	In &_begin,
	In const &_end,
	Grammar const &_grammar
)
{
	sge::parse::result_code const result_code(
		_retval
		?
			_begin
			==
			_end
			?
				sge::parse::result_code::ok
			:
				sge::parse::result_code::partial
		:
			sge::parse::result_code::failure
	);

	return
		sge::parse::result(
			result_code
			,
			result_code
			==
			sge::parse::result_code::ok
			?
				sge::parse::optional_error_string()
			:
				_grammar.error_string()
				?
					_grammar.error_string()
				:
					sge::parse::optional_error_string(
						sge::parse::error_string(
							FCPPT_TEXT("Parsing failed without an error, probably trailing garbage: \"")
							+
							fcppt::string(
								_begin,
								_end
							)
							+
							FCPPT_TEXT('"')
						)
					)
		);
}

}
}

#endif
