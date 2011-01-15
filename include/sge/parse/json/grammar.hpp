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
#include <sge/parse/encoding.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/info_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_directive.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/value.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/spirit/home/phoenix/statement/throw.hpp>

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
		encoding::space_type
	>
{
public:
	typedef encoding::space_type space_type;

	grammar()
	:
		grammar::base_type(
			object_
		)
	{
		using encoding::char_;
		using boost::spirit::lit;
		using boost::spirit::lexeme;
		using boost::spirit::labels::_val;
		using boost::spirit::labels::_1;

		null_ =
			lit(
				FCPPT_TEXT("null")
			)[
				_val = boost::phoenix::construct<null>()
			];

		bool_ =
			lit(
				FCPPT_TEXT("true")
			)[
				_val = true
			]
			| lit(
				FCPPT_TEXT("false")
			)[
				_val = false
			];

		quoted_string_ %=
			lexeme[
				lit(FCPPT_TEXT('"'))
				> *(
					(
						~char_(FCPPT_TEXT("\\\""))
					)
					|
					(
						lit(FCPPT_TEXT('\\'))
						>> char_
					)
				)
				> lit(FCPPT_TEXT('"'))
			];

		array_ %=
			(
				lit(FCPPT_TEXT('['))
				> -(
					value_
					% lit(FCPPT_TEXT(','))
				)
				> lit(FCPPT_TEXT(']'))
			);

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
			> lit(FCPPT_TEXT(':'))
			> value_;

		object_ %=
			(
				lit(FCPPT_TEXT('{'))
				> -(
					member_
					% lit(FCPPT_TEXT(','))
				)
				> lit(FCPPT_TEXT('}'))
			);

		null_.name(
			"null"
		);

		bool_.name(
			"bool"
		);

		quoted_string_.name(
			"string"
		);

		array_.name(
			"array"
		);

		value_.name(
			"value"
		);

		member_.name(
			"member"
		);

		object_.name(
			"object"
		);

		boost::spirit::qi::on_error<
			boost::spirit::qi::fail
		>(
			object_,
			boost::phoenix::throw_(
				boost::phoenix::construct<
					parse::exception
				>(
					boost::phoenix::val(
						FCPPT_TEXT("Json parsing failed: \"")
					)
					+
					boost::phoenix::construct<
						fcppt::string
					>(
						boost::spirit::qi::labels::_1,
						boost::spirit::qi::labels::_3
					)
					+
					FCPPT_TEXT("\" - expected ")
					+
					boost::phoenix::bind(
						&info_to_string,
						boost::spirit::qi::labels::_4
					)
					+
					FCPPT_TEXT(" here.")
				)
			)
		);
	}
private:
	boost::spirit::qi::int_parser<
		int_type
	> int_;

	boost::spirit::qi::real_parser<
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
