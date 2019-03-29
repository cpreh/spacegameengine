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


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/grammar.hpp>
#include <sge/parse/ini/grammar_base_fwd.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/skipper.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/parse/as_struct.hpp>
#include <fcppt/parse/char_set.hpp>
#include <fcppt/parse/construct.hpp>
#include <fcppt/parse/grammar_impl.hpp>
#include <fcppt/parse/literal.hpp>
#include <fcppt/parse/make_ignore.hpp>
#include <fcppt/parse/make_lexeme.hpp>
#include <fcppt/parse/result_of.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/not.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/repetition_plus.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

fcppt::parse::char_set
eol()
{
	return
		fcppt::parse::char_set{'\n'};
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::parse::ini::grammar::grammar()
:
	sge::parse::ini::grammar_base{
		fcppt::make_cref(
			this->ini_
		),
		sge::parse::ini::skipper()
	},
	entry_{
		this->make_base(
			fcppt::parse::as_struct<
				sge::parse::ini::entry
			>(
				!fcppt::parse::literal{'['}
				>>
				fcppt::parse::construct<
					sge::parse::ini::entry_name
				>(
					+~fcppt::parse::char_set{'='}
				)
				>>
				fcppt::parse::literal{'='}
				>>
				fcppt::parse::construct<
					sge::parse::ini::value
				>(
					fcppt::parse::make_lexeme(
						*~eol()
					)
				)
				>> fcppt::parse::make_ignore(+eol())
			)
		)
	},
	header_{
		this->make_base(
			fcppt::parse::make_lexeme(
				fcppt::parse::literal{'['}
				>> +(
					~fcppt::parse::char_set{']', '\n'}
					// TODO
	//				-
	//				eol()
				)
				>> fcppt::parse::literal{']'}
			)
			>> fcppt::parse::make_ignore(+eol())
		)
	},
	section_{
		this->make_base(
			fcppt::parse::as_struct<
				sge::parse::ini::section
			>(
				fcppt::parse::construct<
					sge::parse::ini::section_name
				>(
					fcppt::make_cref(this->header_)
				)
				>> *fcppt::make_cref(this->entry_)
			)
		)
	},
	section_vector_{
		this->make_base(
			*fcppt::make_cref(this->section_)
		)
	},
	ini_{
		this->make_base(
			fcppt::parse::construct<
				sge::parse::ini::start
			>(
				fcppt::make_cref(this->section_vector_)
			)
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::parse::ini::grammar::~grammar()
{
}
