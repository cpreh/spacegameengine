/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/parse/install_error_handler.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/ini/grammar_decl.hpp>
#include <sge/parse/ini/detail/adapt_entry.hpp>
#include <sge/parse/ini/detail/adapt_section.hpp>
#include <sge/parse/ini/detail/adapt_start.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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
	entry_(),
	header_(),
	section_(),
	section_vector_(),
	ini_(),
	error_string_()
{
	using sge::parse::encoding::char_;
	using boost::spirit::lit;
	using boost::spirit::lexeme;
	using boost::spirit::eol;

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

	entry_ %=
		!char_(FCPPT_TEXT('['))
		>> +~char_(FCPPT_TEXT('='))
		>> lit(FCPPT_TEXT('='))
		>>
		lexeme[
			*(char_ - eol)
		]
		>> +eol;

	header_ %=
		lexeme[
			lit(FCPPT_TEXT('['))
			>> +(
				~char_(FCPPT_TEXT(']'))
				-
				eol
			)
			>> lit(FCPPT_TEXT(']'))
		]
		>> +eol;

	section_ %=
		header_
		>> *entry_;

	section_vector_ %=
		*section_;

	ini_ %=
		section_vector_;

	sge::parse::install_error_handler(
		fcppt::make_ref(
			ini_
		),
		fcppt::make_ref(
			error_string_
		)
	);

FCPPT_PP_POP_WARNING
}

template<
	typename In
>
sge::parse::ini::grammar<
	In
>::~grammar()
{
}

template<
	typename In
>
sge::parse::optional_error_string const &
sge::parse::ini::grammar<
	In
>::error_string() const
{
	return
		error_string_;
}

#endif
