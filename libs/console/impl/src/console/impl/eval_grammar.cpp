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


#include <sge/console/impl/eval_grammar.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/parse/basic_char_set.hpp>
#include <fcppt/parse/basic_literal.hpp>
#include <fcppt/parse/epsilon.hpp>
#include <fcppt/parse/grammar_impl.hpp>
#include <fcppt/parse/make_ignore.hpp>
#include <fcppt/parse/separator.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/repetition_plus.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

typedef
fcppt::parse::basic_literal<
	sge::font::char_type
>
literal;

typedef
fcppt::parse::basic_char_set<
	sge::font::char_type
>
char_set;

auto
space()
{
	return
		char_set{
			SGE_FONT_LIT(' '),
			SGE_FONT_LIT('\t')
		};
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::impl::eval_grammar::eval_grammar()
:
	eval_grammar::grammar_base{
		fcppt::make_cref(
			this->start_
		),
		fcppt::parse::epsilon()
	},
	word_{
		this->make_base(
			+~space()
		)
	},
	quoted_string_{
		this->make_base(
			literal{SGE_FONT_LIT('"')}
			>>
			+(~char_set{SGE_FONT_LIT('"')})
			>>
			literal{SGE_FONT_LIT('"')}
		)
	},
	argument_{
		this->make_base(
			fcppt::make_cref(
				this->quoted_string_
			)
			|
			fcppt::make_cref(
				this->word_
			)
		)
	},
	start_{
		this->make_base(
			fcppt::parse::separator{
				fcppt::make_cref(
					this->argument_
				),
				fcppt::parse::make_ignore(
					+space()
				)
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::console::impl::eval_grammar::~eval_grammar()
{
}
