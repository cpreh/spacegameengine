//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
		sge::parse::ini::grammar_base::make_base(
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
		sge::parse::ini::grammar_base::make_base(
			fcppt::parse::make_lexeme(
				fcppt::parse::literal{'['}
				>> +(
					~fcppt::parse::char_set{']', '\n'}
					// TODO(philipp)
	//				-
	//				eol()
				)
				>> fcppt::parse::literal{']'}
			)
			>> fcppt::parse::make_ignore(+eol())
		)
	},
	section_{
		sge::parse::ini::grammar_base::make_base(
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
		sge::parse::ini::grammar_base::make_base(
			*fcppt::make_cref(this->section_)
		)
	},
	ini_{
		sge::parse::ini::grammar_base::make_base(
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
= default;
