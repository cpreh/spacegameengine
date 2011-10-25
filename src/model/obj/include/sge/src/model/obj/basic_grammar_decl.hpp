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


#ifndef SGE_SRC_MODEL_OBJ_BASIC_GRAMMAR_DECL_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_BASIC_GRAMMAR_DECL_HPP_INCLUDED

#include <sge/model/obj/face_fwd.hpp>
#include <sge/model/obj/face_point_fwd.hpp>
#include <sge/model/obj/mesh_fwd.hpp>
#include <sge/model/obj/normal_fwd.hpp>
#include <sge/model/obj/texcoord_fwd.hpp>
#include <sge/model/obj/vertex_fwd.hpp>
#include <sge/src/model/obj/basic_grammar_fwd.hpp>
#include <sge/src/model/obj/parse_state_fwd.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <boost/spirit/home/lex/qi/in_state.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace model
{
namespace obj
{

template<
	typename Iterator,
	typename Lexer
>
class basic_grammar
:
	public
	boost::spirit::qi::grammar<
		Iterator,
		boost::spirit::qi::in_state_skipper<
			Lexer,
			fcppt::char_type const *
		>
	>
{
	FCPPT_NONCOPYABLE(
		basic_grammar
	);
public:
	template<
		typename TokenDef
	>
	basic_grammar(
		TokenDef const &_tokens,
		obj::parse_state &
	);

	~basic_grammar();
private:
	typedef boost::spirit::qi::in_state_skipper<
		Lexer,
		fcppt::char_type const *
	> skipper;

	boost::spirit::qi::rule<
		Iterator,
		obj::vertex(),
		skipper
	> vertex_;

	boost::spirit::qi::rule<
		Iterator,
		obj::texcoord(),
		skipper
	> texcoord_;

	boost::spirit::qi::rule<
		Iterator,
		obj::normal(),
		skipper
	> normal_;

	boost::spirit::qi::rule<
		Iterator,
		obj::face_point(),
		skipper
	> face_point_;

	boost::spirit::qi::rule<
		Iterator,
		obj::face(),
		skipper
	> face_;

	boost::spirit::qi::rule<
		Iterator,
		skipper
	> mtllib_;

	boost::spirit::qi::rule<
		Iterator,
		skipper
	> usemtl_;

	boost::spirit::qi::rule<
		Iterator,
		skipper
	> smoothing_;

	boost::spirit::qi::rule<
		Iterator,
		obj::mesh(),
		skipper
	> mesh_;

	boost::spirit::qi::rule<
		Iterator,
		skipper
	> line_;

	boost::spirit::qi::rule<
		Iterator,
		skipper
	> file_;

	obj::parse_state &state_;
};

}
}
}

#endif
