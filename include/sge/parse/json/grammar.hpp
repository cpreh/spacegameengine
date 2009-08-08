/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED

#include <sge/parse/json/detail/adapt_array.hpp>
#include <sge/parse/json/detail/adapt_member.hpp>
#include <sge/parse/json/detail/adapt_object.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/text.hpp>

// TODO: include only the headers which are needed!
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>

namespace sge
{
namespace parse
{
namespace json
{

template<
	typename In
>
class grammar
:
public boost::spirit::qi::grammar<
	In,
	object(),
	boost::spirit::ascii::space_type
>{
public:
	typedef boost::spirit::ascii::space_type space_type;

	grammar()
	:
		grammar::base_type(
			object_
		)
	{
		using boost::spirit::char_;
		using boost::spirit::lit;
		using boost::spirit::lexeme;
		using boost::spirit::arg_names::_val;
		using boost::phoenix::construct;
		using boost::phoenix::val;

		null_ =
			lit(
				SGE_TEXT("null")
			)[
				_val = construct<null>()
			];

		bool_ =
			lit(
				SGE_TEXT("true")
			)[
				_val = true
			]
			| lit(
				SGE_TEXT("false")
			)[
				_val = false
			];

		quoted_string_ %=
			lexeme[
				char_(SGE_TEXT('"'))
				>> *(
					(
						char_
						- char_(SGE_TEXT('\\'))
						- char_(SGE_TEXT('"'))
					)
					| (
						char_(SGE_TEXT('\\'))
						>> char_
					)
				)
				>> char_(SGE_TEXT('"'))
			];

		array_ %=
			char_(SGE_TEXT('['))
			>> -(
				value_ % char_(SGE_TEXT(','))
			)
			>> char_(SGE_TEXT(']'));

		value_ %=
			object_
			| array_ 
			| bool_
			| quoted_string_
			| strict_float
			| int_
			| null_;

		member_ %=
			quoted_string_
			>> char_(SGE_TEXT(':'))
			>> value_;

		object_ %=
			char_(SGE_TEXT('{'))
			>> -(
				member_
				% char_(SGE_TEXT(','))
			)
			>> char_(SGE_TEXT('}'));
	}
private:
	boost::spirit::qi::int_spec<
		int_type
	> int_;

	boost::spirit::qi::real_spec<
		float_type,
		boost::spirit::qi::strict_real_policies<
			float_type	
		>
	> strict_float;

	boost::spirit::qi::rule<
		In,
		null(),
		space_type
	> null_;

	boost::spirit::qi::rule<
		In,
		bool(),
		space_type
	> bool_;

	boost::spirit::qi::rule<
		In,
		string(),
		space_type
	> quoted_string_;

	boost::spirit::qi::rule<
		In,
		array(),
		space_type
	> array_;

	boost::spirit::qi::rule<
		In,
		value(),
		space_type
	> value_;

	boost::spirit::qi::rule<
		In,
		member(),
		space_type
	> member_;

	boost::spirit::qi::rule<
		In,
		object(),
		space_type
	> object_;
};

}
}
}

#endif
