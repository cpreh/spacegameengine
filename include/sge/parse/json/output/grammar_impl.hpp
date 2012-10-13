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


#ifndef SGE_PARSE_JSON_OUTPUT_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_OUTPUT_GRAMMAR_IMPL_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/json/detail/adapt_array.hpp>
#include <sge/parse/json/detail/adapt_object.hpp>
#include <sge/parse/json/detail/adapt_start.hpp>
#include <sge/parse/json/output/grammar_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/karma_bool.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_int.hpp>
#include <boost/spirit/include/karma_operator.hpp>
#include <boost/spirit/include/karma_real.hpp>
#include <boost/spirit/include/karma_rule.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Out
>
sge::parse::json::output::grammar<
	Out
>::grammar()
:
	grammar::base_type(
		start_
	)
{
	namespace encoding = parse::encoding;

	namespace karma = boost::spirit::karma;

	null_ %=
		karma::lit(FCPPT_TEXT("null"));

	quoted_string_ %=
		karma::lit(FCPPT_TEXT('"'))
		<< *encoding::char_
		<< karma::lit(FCPPT_TEXT('"'));

	array_ %=
		karma::lit(FCPPT_TEXT('['))
		<< -(value_ % karma::lit(FCPPT_TEXT(", ")))
		<< karma::lit(FCPPT_TEXT(']'));

	value_ %=
		object_
		| array_
		| karma::bool_
		| quoted_string_
		| float_
		| int_
		| null_;

	member_ %=
		quoted_string_
		<< karma::lit(FCPPT_TEXT(':'))
		<< value_;

	object_ %=
		karma::lit(FCPPT_TEXT('{'))
		<< -(member_ % karma::lit(FCPPT_TEXT(", ")))
		<< karma::lit(FCPPT_TEXT('}'));

	start_ %=
		array_
		|
		object_;
}

template<
	typename Out
>
sge::parse::json::output::grammar<
	Out
>::~grammar()
{
}

#endif
