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


#ifndef SGE_MODEL_OBJ_BASIC_TOKENS_IMPL_HPP_INCLUDED
#define SGE_MODEL_OBJ_BASIC_TOKENS_IMPL_HPP_INCLUDED

#include "basic_tokens_decl.hpp"
#include <fcppt/text.hpp>

template<
	typename Lexer
>
sge::model::obj::basic_tokens<Lexer>::basic_tokens()
{
	this->self.add_pattern(
		FCPPT_TEXT("INT"),
		FCPPT_TEXT("-?[0-9]+")
	);

	this->self.add_pattern(
		FCPPT_TEXT("FLOAT"),
		FCPPT_TEXT("-?[0-9]+\\.[0-9]*")
	);

	this->self.add_pattern(
		FCPPT_TEXT("NAME"),
		FCPPT_TEXT("[^\t\n /#]+")
	);

	int_ = FCPPT_TEXT("{INT}");

	float_ = FCPPT_TEXT("{FLOAT}");

	name_ = FCPPT_TEXT("{NAME}");

	vt_ = FCPPT_TEXT("vt");

	vn_ = FCPPT_TEXT("vn");

	mtllib_ = FCPPT_TEXT("mtllib");

	usemtl_ = FCPPT_TEXT("usemtl");

	this->self.add
		(int_)
		(float_)
		(vt_)
		(vn_)
		(mtllib_)
		(usemtl_)
		(FCPPT_TEXT('v'))
		(FCPPT_TEXT('n'))
		(FCPPT_TEXT('f'))
		(FCPPT_TEXT('o'))
		(FCPPT_TEXT('s'))
		(FCPPT_TEXT('/'))
		(FCPPT_TEXT('\n'))
		(name_)
	;

	this->self(
		FCPPT_TEXT("WS")
	)
		=
		boost::spirit::lex::token_def<>(
			FCPPT_TEXT("[ \\t]+")
		)
		|
		FCPPT_TEXT("#[^\\n]*\\n")
		;
}

template<
	typename Lexer
>
sge::model::obj::basic_tokens<Lexer>::~basic_tokens()
{
}

#endif
