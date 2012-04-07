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


#ifndef SGE_PARSE_INI_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_GRAMMAR_IMPL_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/ini/grammar_decl.hpp>
#include <sge/parse/ini/detail/adapt_entry.hpp>
#include <sge/parse/ini/detail/adapt_section.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_eol.hpp>
#include <boost/spirit/include/qi_lexeme.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename In
>
sge::parse::ini::grammar<
	In
>::grammar()
:
	grammar::base_type(
		ini_
	),
	char_seq_(),
	entry_(),
	header_(),
	section_(),
	ini_()
{
	using sge::parse::encoding::char_;
	using boost::spirit::lit;
	using boost::spirit::lexeme;
	using boost::spirit::eol;

	char_seq_ %=
		+(
			char_
			- eol
		);

	entry_ %=
		!char_(FCPPT_TEXT('['))
		>> +~char_(FCPPT_TEXT('='))
		>> lit(FCPPT_TEXT('='))
		>> char_seq_
		>> eol;


	header_ %=
		lexeme[
			FCPPT_TEXT('[')
			>> +~char_(FCPPT_TEXT(']'))
			>> FCPPT_TEXT(']')
		]
		>> eol;

	section_ %=
		header_
		>> *entry_;

	ini_ %=
		*section_;
}

template<
	typename In
>
sge::parse::ini::grammar<
	In
>::~grammar()
{
}

#endif
