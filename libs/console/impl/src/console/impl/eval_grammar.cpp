//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/console/impl/eval_grammar.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/parse/basic_char_set.hpp>
#include <fcppt/parse/basic_literal.hpp>
#include <fcppt/parse/grammar_impl.hpp>
#include <fcppt/parse/make_ignore.hpp>
#include <fcppt/parse/separator.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/repetition_plus.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/parse/skipper/epsilon.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

using literal = fcppt::parse::basic_literal<sge::font::char_type>;

using char_set = fcppt::parse::basic_char_set<sge::font::char_type>;

auto space() { return char_set{SGE_FONT_LIT(' '), SGE_FONT_LIT('\t')}; }

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::impl::eval_grammar::eval_grammar()
    : eval_grammar::grammar_base{fcppt::make_cref(this->start_), fcppt::parse::skipper::epsilon()},
      word_{grammar_base::make_base(+~space())},
      quoted_string_{grammar_base::make_base(
          literal{SGE_FONT_LIT('"')} >> +(~char_set{SGE_FONT_LIT('"')}) >>
          literal{SGE_FONT_LIT('"')})},
      argument_{grammar_base::make_base(
          fcppt::make_cref(this->quoted_string_) | fcppt::make_cref(this->word_))},
      start_{grammar_base::make_base(fcppt::parse::separator{
          fcppt::make_cref(this->argument_), fcppt::parse::make_ignore(+space())})}
{
}

FCPPT_PP_POP_WARNING

sge::console::impl::eval_grammar::~eval_grammar() = default;
