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


#ifndef SGE_PARSE_JSON_OUTPUT_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_JSON_OUTPUT_GRAMMAR_HPP_INCLUDED

#include <sge/parse/json/detail/adapt_array.hpp>
#include <sge/parse/json/detail/adapt_member.hpp>
#include <sge/parse/json/detail/adapt_object.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/encoding.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>

#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_grammar.hpp>
#include <boost/spirit/include/karma_operator.hpp>
#include <boost/spirit/include/karma_rule.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_numeric.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace parse
{
namespace json
{
namespace output
{

template<
	typename Out
>
class grammar
:
	public boost::spirit::karma::grammar<
		Out,
		object()
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::base_type(
			object_
		)
	{
		using encoding::char_;
		using boost::spirit::lit;
		using boost::spirit::karma::bool_;

		null_ %=
			lit(FCPPT_TEXT("null"));

		quoted_string_ %=
			lit(FCPPT_TEXT('"'))
			<< *char_
			<< lit(FCPPT_TEXT('"'));

		array_ %=
			lit(FCPPT_TEXT('['))
			<< -(value_ % lit(FCPPT_TEXT(", ")))
			<< lit(FCPPT_TEXT(']'));

		value_ %=
			object_
			| array_
			| bool_
			| quoted_string_
			| float_
			| int_
			| null_;

		member_ %=
			quoted_string_
			<< lit(FCPPT_TEXT(':'))
			<< value_;

		object_ %=
			lit(FCPPT_TEXT('{'))
			<< -(member_ % lit(FCPPT_TEXT(", ")))
			<< lit(FCPPT_TEXT('}'));
	}

	~grammar()
	{
	}
private:
	boost::spirit::karma::int_generator<
		int_type
	> int_;

	boost::spirit::karma::real_generator<
		float_type
	> float_;

	boost::spirit::karma::rule<
		Out,
		null
	> null_;

	boost::spirit::karma::rule<
		Out,
		string()
	> quoted_string_;

	boost::spirit::karma::rule<
		Out,
		array()
	> array_;

	boost::spirit::karma::rule<
		Out,
		value()
	> value_;

	boost::spirit::karma::rule<
		Out,
		member()
	> member_;

	boost::spirit::karma::rule<
		Out,
		object()
	> object_;
};

}
}
}
}

#endif
