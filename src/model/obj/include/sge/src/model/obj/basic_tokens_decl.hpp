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


#ifndef SGE_SRC_MODEL_OBJ_BASIC_TOKENS_DECL_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_BASIC_TOKENS_DECL_HPP_INCLUDED

#include <sge/model/obj/index.hpp>
#include <sge/model/obj/scalar.hpp>
#include <sge/src/model/obj/basic_tokens_fwd.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{

template<
	typename Lexer
>
struct basic_tokens
:
	boost::spirit::lex::lexer<
		Lexer
	>
{
	FCPPT_NONCOPYABLE(
		basic_tokens
	);
public:
	basic_tokens();

	~basic_tokens();

	boost::spirit::lex::token_def<
		boost::spirit::unused_type,
		fcppt::char_type
	> vt_;

	boost::spirit::lex::token_def<
		boost::spirit::unused_type,
		fcppt::char_type
	> vn_;

	boost::spirit::lex::token_def<
		boost::spirit::unused_type,
		fcppt::char_type
	> mtllib_;

	boost::spirit::lex::token_def<
		boost::spirit::unused_type,
		fcppt::char_type
	> usemtl_;

	boost::spirit::lex::token_def<
		obj::index,
		fcppt::char_type
	> int_;

	boost::spirit::lex::token_def<
		obj::scalar,
		fcppt::char_type
	> float_;

	boost::spirit::lex::token_def<
		fcppt::string,
		fcppt::char_type
	> name_;
};

}
}
}

#endif
