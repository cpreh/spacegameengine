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


#ifndef SGE_PARSE_JSON_PARSE_RANGE_HPP_INCLUDED
#define SGE_PARSE_JSON_PARSE_RANGE_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/make_result.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/json/grammar.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename In
>
sge::parse::result const
parse_range(
	In &_beg,
	In const _end,
	sge::parse::json::start &_result
)
{
	sge::parse::json::grammar<
		In
	> parser;

	return
		sge::parse::make_result(
			boost::spirit::qi::phrase_parse(
				_beg,
				_end,
				parser,
				sge::parse::encoding::space,
				_result
			),
			_beg,
			_end,
			parser
		);
}

}
}
}

#endif
