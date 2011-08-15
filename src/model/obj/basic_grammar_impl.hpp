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


#ifndef SGE_MODEL_OBJ_BASIC_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_MODEL_OBJ_BASIC_GRAMMAR_IMPL_HPP_INCLUDED

#include "basic_grammar_decl.hpp"
#include "adapt_face.hpp"
#include "adapt_face_point.hpp"
#include "adapt_mesh.hpp"
#include "adapt_normal.hpp"
#include "adapt_texcoord.hpp"
#include "adapt_vertex.hpp"
#include "parse_state.hpp"
#include <sge/model/obj/mesh.hpp>
#include <sge/model/obj/optional_index.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/spirit/include/qi_core.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_optional.hpp>
#include <boost/spirit/include/qi_repeat.hpp>

template<
	typename Iterator,
	typename Lexer
>
template<
	typename TokenDef
>
sge::model::obj::basic_grammar<
	Iterator,
	Lexer
>::basic_grammar(
	TokenDef const &_tokens,
	obj::parse_state &_state
)
:
	basic_grammar::base_type(
		file_
	),
	state_(
		_state
	)
{
	vertex_ %=
		boost::spirit::lit(
			FCPPT_TEXT('v')
		)
		>>
		_tokens.float_
		>>
		_tokens.float_
		>>
		_tokens.float_
		>>
		-_tokens.float_
		;

	texcoord_ %=
		_tokens.vt_
		>>
		_tokens.float_
		>>
		_tokens.float_
		>>
		-_tokens.float_
		;

	normal_ %=
		_tokens.vn_
		>>
		_tokens.float_
		>>
		_tokens.float_
		>>
		_tokens.float_
		;

	face_point_ %=
		(
			_tokens.int_
			>>
			boost::spirit::lit(
				FCPPT_TEXT('/')
			)
			>>
			-_tokens.int_
			>>
			boost::spirit::lit(
				FCPPT_TEXT('/')
			)
			>>
			-_tokens.int_
		)
		|
		(
			_tokens.int_
			>>
			boost::spirit::qi::attr(
				obj::optional_index()
			)
			>>
			boost::spirit::qi::attr(
				obj::optional_index()
			)
		)
		;

	face_ %=
		boost::spirit::lit(
			FCPPT_TEXT('f')
		)
		>>
		boost::spirit::qi::repeat(
			3,
			boost::spirit::qi::inf
		)
		[
			face_point_
		]
		;

	mtllib_ =
		_tokens.mtllib_
		>>
		_tokens.name_
		;

	usemtl_ =
		_tokens.usemtl_
		>>
		_tokens.name_
		;

	smoothing_ =
		boost::spirit::lit(
			FCPPT_TEXT('s')
		)
		>>
		(
			_tokens.name_
			|
			_tokens.int_
		)
		;

	mesh_ %=
		boost::spirit::lit(
			FCPPT_TEXT('o')
		)
		>>
		_tokens.name_
		;

	line_ =
		(
			vertex_[
				boost::phoenix::push_back(
					boost::phoenix::bind(
						&obj::parse_state::vertices_,
						boost::phoenix::ref(
							state_
						)
					),
					boost::spirit::qi::_1
				)
			]
			|
			texcoord_[
				boost::phoenix::push_back(
					boost::phoenix::bind(
						&obj::parse_state::texcoords_,
						boost::phoenix::ref(
							state_
						)
					),
					boost::spirit::qi::_1
				)
			]
			|
			normal_[
				boost::phoenix::push_back(
					boost::phoenix::bind(
						&obj::parse_state::normals_,
						boost::phoenix::ref(
							state_
						)
					),
					boost::spirit::qi::_1
				)
			]
			|
			face_[
				boost::phoenix::push_back(
					boost::phoenix::bind(
						&obj::mesh::faces_,
						boost::phoenix::back(
							boost::phoenix::bind(
								&obj::parse_state::meshes_,
								boost::phoenix::ref(
									state_
								)
							)
						)
					),
					boost::spirit::qi::_1
				)
			]
			|
			mtllib_
			|
			usemtl_
			|
			smoothing_
			|
			mesh_[
				boost::phoenix::push_back(
					boost::phoenix::bind(
						&obj::parse_state::meshes_,
						boost::phoenix::ref(
							state_
						)
					),
					boost::spirit::qi::_1
				)
			]
		)
		>>
		boost::spirit::lit(
			FCPPT_TEXT('\n')
		)
		;

	file_ =
		*line_;

#if 0
	vertex_.name("vertex");
	texcoord_.name("texcoord");
	normal_.name("normal");
	face_point_.name("face_point");
	face_.name("face");
	mtllib_.name("mtllib");
	usemtl_.name("usemtl");
	smoothing_.name("smoothing");
	mesh_.name("mesh");
	line_.name("line");
	file_.name("file");

	BOOST_SPIRIT_DEBUG_NODE(vertex_);
	BOOST_SPIRIT_DEBUG_NODE(texcoord_);
	BOOST_SPIRIT_DEBUG_NODE(normal_);
	BOOST_SPIRIT_DEBUG_NODE(face_point_);
	BOOST_SPIRIT_DEBUG_NODE(face_);
	BOOST_SPIRIT_DEBUG_NODE(mtllib_);
	BOOST_SPIRIT_DEBUG_NODE(usemtl_);
	BOOST_SPIRIT_DEBUG_NODE(smoothing_);
	BOOST_SPIRIT_DEBUG_NODE(mesh_);
	BOOST_SPIRIT_DEBUG_NODE(line_);
	BOOST_SPIRIT_DEBUG_NODE(file_);
#endif
	state_.meshes_.push_back(
		obj::mesh()
	);
}

template<
	typename Iterator,
	typename Lexer
>
sge::model::obj::basic_grammar<
	Iterator,
	Lexer
>::~basic_grammar()
{
}

#endif
