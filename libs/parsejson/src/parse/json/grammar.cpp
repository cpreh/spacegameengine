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


#ifndef SGE_PARSE_JSON_GRAMMAR_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_IMPL_HPP_INCLUDED

#include <sge/parse/install_error_handler.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/json/grammar_decl.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/detail/adapt_array.hpp>
#include <sge/parse/json/detail/adapt_object.hpp>
#include <sge/parse/json/detail/adapt_start.hpp>
#include <sge/parse/json/detail/insert_member.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/compiler.hpp>


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
				fcppt::parse::string{
					"null"
				},
				sge::parse::json::null{}
			)
		)
	}
	bool_{
		this->make_base(
			fcppt::parse::convert_const(
				fcppt::parse::string(
					"true"
				),
				true
			)
			|
			fcppt::parse::convert_const(
				fcppt::parse::string(
					"false"
				),
				false
			)
		)
	},
	quoted_string_{
		this->make_base(
			fcppt::parse::literal{'"'}
			>>
			fcppt::parse::make_lexeme(
				*~fcppt::parse::char_set{'"'}
			)
			>>
			fcppt::parse::literal{'"'}
		)
	},
	array_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::array
			>(
				fcppt::parse::literal('[')
				>>
				fcppt::parse::separator{
					fcppt::parse::make_recursive(
						fcppt::make_cref(
							this->value_
						)
					),
					fcppt::parse::literal(',')
				}
				>>
				fcppt::parse::literal(']')
			)
		)
	},
	object_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::json::object
			>(
				fcppt::parse::make_convert(
					fcppt::parse::literal{'{'}
					>>
					fcppt::parse::separator{
						fcppt::make_cref(
							this->quoted_string_
						)
						>>
						fcppt::parse::literal{':'}
						>>
						fcppt::parse::make_recursive(
							fcppt::make_cref(
								this->value_
							)
						),
						fcppt::parse::literal{','}
					}
					>>
					fcppt::parse::literal{'}'},
					&make_members
				)
			)
		)
	},
	value_{
		this->make_base(
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
			fcppt::parse::float_<
				float
			>{}
			|
			fcppt::parse::int_<
				int
			>{}
			|
			fcppt::make_cref(
				this->null_
			)
		)
	},
	start_{
		this->make_base(
			fcppt::make_cref(
				this->array_
			)
			|
			fcppt::make_cref(
				this->object_
			)
		)
	}
{
}

sge::parse::json::grammar::~grammar()
{
}

#endif
