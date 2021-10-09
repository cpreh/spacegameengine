//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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
#include <fcppt/parse/list.hpp>
#include <fcppt/parse/make_convert_if.hpp>
#include <fcppt/parse/make_fatal.hpp>
#include <fcppt/parse/make_lexeme.hpp>
#include <fcppt/parse/make_recursive.hpp>
#include <fcppt/parse/operators/alternative.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/not.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

using literal = fcppt::parse::basic_literal<sge::charconv::utf8_char>;

using char_set = fcppt::parse::basic_char_set<sge::charconv::utf8_char>;

using string = fcppt::parse::basic_string<sge::charconv::utf8_char>;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::parse::json::grammar::grammar()
    : sge::parse::json::grammar_base{fcppt::make_cref(this->start_), sge::parse::json::skipper()},
      null_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::convert_const(string{"null"}, sge::parse::json::null{}))},
      bool_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::convert_const(string("true"), true) |
          fcppt::parse::convert_const(string("false"), false))},
      quoted_string_{sge::parse::json::grammar_base::make_base(
          literal{'"'} >> fcppt::parse::make_lexeme(*~char_set{'"'}) >> literal{'"'})},
      array_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::construct<sge::parse::json::array>(fcppt::parse::list{
              literal('['),
              fcppt::parse::make_recursive(fcppt::make_cref(this->value_)),
              literal{','},
              literal(']')}))},
      object_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::construct<sge::parse::json::object>(fcppt::parse::make_convert_if(
              fcppt::parse::list{
                  literal{'{'},
                  fcppt::parse::make_fatal(
                      fcppt::make_cref(this->quoted_string_) >> literal{':'} >>
                      fcppt::parse::make_recursive(fcppt::make_cref(this->value_))),
                  literal{','},
                  literal{'}'}},
              &sge::parse::json::impl::make_members)))},
      value_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::make_fatal(fcppt::parse::construct<sge::parse::json::value>(
              fcppt::make_cref(this->object_) | fcppt::make_cref(this->array_) |
              fcppt::make_cref(this->bool_) | fcppt::make_cref(this->quoted_string_) |
              (fcppt::parse::int_<sge::parse::json::int_type>{} >> !literal{'.'}) |
              fcppt::parse::float_<sge::parse::json::float_type>{} |
              fcppt::make_cref(this->null_))))},
      start_{sge::parse::json::grammar_base::make_base(
          fcppt::parse::construct<sge::parse::json::start>(
              fcppt::make_cref(this->array_) | fcppt::make_cref(this->object_)))}
{
}

FCPPT_PP_POP_WARNING

sge::parse::json::grammar::~grammar() = default;
