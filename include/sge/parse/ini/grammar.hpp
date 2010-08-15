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


#ifndef SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED

#include <sge/parse/ini/detail/adapt_entry.hpp>
#include <sge/parse/ini/detail/adapt_section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/string.hpp>
#include <sge/parse/encoding.hpp>
#include <fcppt/text.hpp>

#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_directive.hpp>

namespace sge
{
namespace parse
{
namespace ini
{

template<
	typename In
>
class grammar
:
	public boost::spirit::qi::grammar<
		In,
		section_vector(),
		encoding::blank_type
	>
{
public:
	grammar()
	:
		grammar::base_type(
			ini_
		)
	{
		using encoding::char_;
		using boost::spirit::lit;
		using boost::spirit::lexeme;

		char_seq %= +(char_ - lit(FCPPT_TEXT('\n')));

		entry_ %=
			!char_(FCPPT_TEXT('['))
			>> +(
				char_
				- lit(FCPPT_TEXT('='))
			)
			>> lit(FCPPT_TEXT('='))
			>> char_seq
			>> lit(FCPPT_TEXT('\n'));

		header_ %=
			lexeme[
				FCPPT_TEXT('[')
				>> +(
					char_ - FCPPT_TEXT(']')
				)
				>> FCPPT_TEXT(']')
			]
			>> lit(FCPPT_TEXT('\n'));

		section_ %=
			header_
			>> *entry_;

		ini_ %=
			*section_;
	}
private:
	boost::spirit::qi::rule<
		In,
		string(),
		encoding::blank_type
	> char_seq;

	boost::spirit::qi::rule<
		In,
		entry(),
		encoding::blank_type
	> entry_;

	boost::spirit::qi::rule<
		In,
		string(),
		encoding::blank_type
	> header_;

	boost::spirit::qi::rule	<
		In,
		section(),
		encoding::blank_type
	> section_;

	boost::spirit::qi::rule<
		In,
		section_vector(),
		encoding::blank_type
	> ini_;
};

}
}
}

#endif
