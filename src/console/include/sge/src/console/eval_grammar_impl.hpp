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


#ifndef SGE_SRC_CONSOLE_EVAL_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_SRC_CONSOLE_EVAL_GRAMMAR_IMPL_HPP_INCLUDED

#include <sge/font/lit.hpp>
#include <sge/src/console/eval_grammar_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Iterator
>
sge::console::eval_grammar<
	Iterator
>::eval_grammar()
:
	eval_grammar::base_type(
		start_
	),
	word_(),
	quoted_string_(),
	argument_(),
	start_()
{
	namespace encoding = boost::spirit::standard_wide;

	using encoding::char_;
	using encoding::space;

	word_ %=
		+~space;

	quoted_string_ %=
		SGE_FONT_LIT('"')
		>> +(~char_(SGE_FONT_LIT('"')))
		>> SGE_FONT_LIT('"');

	argument_ %=
		quoted_string_
		| word_;

	start_ %=
		argument_ % (+space);
}

template<
	typename Iterator
>
sge::console::eval_grammar<
	Iterator
>::~eval_grammar()
{
}

#endif
