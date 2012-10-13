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


#ifndef SGE_PARSE_JSON_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_IMPL_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/info_to_string.hpp>
#include <sge/parse/json/grammar_decl.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/detail/adapt_array.hpp>
#include <sge/parse/json/detail/adapt_object.hpp>
#include <sge/parse/json/detail/adapt_start.hpp>
#include <sge/parse/json/detail/insert_member.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/spirit_traits/optional_basic.hpp>
#include <fcppt/spirit_traits/variant_basic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/value.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/spirit/home/phoenix/statement/throw.hpp>
#include <boost/spirit/home/phoenix/stl/container.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_directive.hpp>
#include <boost/spirit/include/qi_lexeme.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename In
>
sge::parse::json::grammar<
	In
>::grammar()
:
	grammar::base_type(
		start_
	),
	int_(),
	strict_float_(),
	null_(),
	bool_(),
	quoted_string_(),
	element_vector_(),
	array_(),
	value_wrapper_(),
	member_wrapper_(),
	member_map_(),
	object_(),
	start_()
{
	namespace encoding = parse::encoding;

	namespace qi = boost::spirit::qi;

	null_ =
		qi::lit(
			FCPPT_TEXT("null")
		)[
			qi::_val
			= boost::phoenix::construct<
				json::null
			>()
		];

	bool_ =
		qi::lit(
			FCPPT_TEXT("true")
		)[
			qi::_val = true
		]
		|
		qi::lit(
			FCPPT_TEXT("false")
		)[
			qi::_val = false
		];

	quoted_string_ %=
		boost::spirit::qi::lexeme[
			qi::lit(FCPPT_TEXT('"'))
			> *(
				(
					~encoding::char_(FCPPT_TEXT("\\\""))
				)
				|
				(
					qi::lit(FCPPT_TEXT('\\'))
					>> encoding::char_
				)
			)
			> qi::lit(FCPPT_TEXT('"'))
		];

	element_vector_ =
		value_wrapper_[
			boost::phoenix::push_back(
				boost::spirit::qi::_val,
				boost::phoenix::bind(
					&json::detail::value_wrapper::get,
					boost::spirit::qi::_1
				)
			)
		]
		% qi::lit(FCPPT_TEXT(','));

	array_ %=
		(
			qi::lit(FCPPT_TEXT('['))
			> -element_vector_
			> qi::lit(FCPPT_TEXT(']'))
		);

	value_wrapper_ %=
		object_
		| array_
		| bool_
		| quoted_string_
		| strict_float_
		| int_
		| null_;

	member_wrapper_ %=
		quoted_string_
		> qi::lit(FCPPT_TEXT(':'))
		> value_wrapper_;

	member_map_ =
		member_wrapper_[
			boost::phoenix::bind(
				json::detail::insert_member,
				boost::spirit::qi::_val,
				boost::spirit::qi::_1,
				boost::spirit::qi::_pass
			)
		]
		% qi::lit(FCPPT_TEXT(','));

	object_ %=
		(
			qi::lit(FCPPT_TEXT('{'))
			> -member_map_
			> qi::lit(FCPPT_TEXT('}'))
		);

	start_ %=
		array_
		|
		object_;

	boost::spirit::qi::on_error<
		boost::spirit::qi::fail
	>(
		start_,
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

template<
	typename In
>
sge::parse::json::grammar<
	In
>::~grammar()
{
}

#endif
