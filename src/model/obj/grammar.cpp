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


#include "grammar.hpp"
#include "basic_grammar_impl.hpp"
#include "iterator.hpp"
#include "parse_state_fwd.hpp"
#include "tokens.hpp"

template class
sge::model::obj::basic_grammar<
	sge::model::obj::iterator,
	sge::model::obj::tokens::lexer_def
>;

template
sge::model::obj::basic_grammar<
	sge::model::obj::iterator,
	sge::model::obj::tokens::lexer_def
>::basic_grammar<
	sge::model::obj::tokens
>(
	sge::model::obj::tokens const &,
	sge::model::obj::parse_state &
);
