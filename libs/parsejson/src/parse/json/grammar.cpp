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


#include <sge/charconv/utf8_char.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/grammar.hpp>
#include <sge/parse/json/grammar_base_fwd.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/skipper.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/impl/make_members.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/parse/basic_char_set.hpp>
#include <fcppt/parse/basic_literal.hpp>
#include <fcppt/parse/basic_string.hpp>
#include <fcppt/parse/construct.hpp>
#include <fcppt/parse/convert_const.hpp>
#include <fcppt/parse/float.hpp>
#include <fcppt/parse/grammar_impl.hpp>
#include <fcppt/parse/int.hpp>
#include <fcppt/parse/make_convert_if.hpp>
#include <fcppt/parse/make_lexeme.hpp>
#include <fcppt/parse/make_recursive.hpp>
#include <fcppt/parse/separator.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/not.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/parse/operators/repetition.hpp>


namespace
{

typedef
fcppt::parse::basic_literal<
	sge::charconv::utf8_char
>
literal;

typedef
fcppt::parse::basic_char_set<
	sge::charconv::utf8_char
>
char_set;

typedef
fcppt::parse::basic_string<
	sge::charconv::utf8_char
>
string;

}

sge::parse::json::grammar::grammar()
:
	sge::parse::json::grammar_base{
		fcppt::make_cref(
			this->start_
		),
		sge::parse::json::skipper()
	},
	null_{
		this->make_base(
			fcppt::parse::convert_const(
				string{
					"null"
				},
				sge::parse::json::null{}
			)
		)
	},
	bool_{
		this->make_base(
			fcppt::parse::convert_const(
				string(
					"true"
				),
				true
			)
			|
			fcppt::parse::convert_const(
				string(
					"false"
				),
				false
			)
		)
	},
	quoted_string_{
		this->make_base(
			literal{'"'}
			>>
			fcppt::parse::make_lexeme(
				*~char_set{'"'}
			)
			>>
			literal{'"'}
		)
	},
	array_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::array
			>(
				literal('[')
				>>
				fcppt::parse::separator{
					fcppt::parse::make_recursive(
						fcppt::make_cref(
							this->value_
						)
					),
					literal{','}
				}
				>>
				literal(']')
			)
		)
	},
	object_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::object
			>(
				fcppt::parse::make_convert_if(
					literal{'{'}
					>>
					fcppt::parse::separator{
						fcppt::make_cref(
							this->quoted_string_
						)
						>>
						literal{':'}
						>>
						fcppt::parse::make_recursive(
							fcppt::make_cref(
								this->value_
							)
						),
						literal{','}
					}
					>>
					literal{'}'},
					&sge::parse::json::impl::make_members
				)
			)
		)
	},
	value_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::value
			>(
				fcppt::make_cref(
					this->object_
				)
				|
				fcppt::make_cref(
					this->array_
				)
				|
				fcppt::make_cref(
					this->bool_
				)
				|
				fcppt::make_cref(
					this->quoted_string_
				)
				|
				(
					fcppt::parse::int_<
						sge::parse::json::int_type
					>{}
					>>
					!
					literal{
						'.'
					}
				)
				|
				fcppt::parse::float_<
					sge::parse::json::float_type
				>{}
				|
				fcppt::make_cref(
					this->null_
				)
			)
		)
	},
	start_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::start
			>(
				fcppt::make_cref(
					this->array_
				)
				|
				fcppt::make_cref(
					this->object_
				)
			)
		)
	}
{
}

sge::parse::json::grammar::~grammar()
{
}
