//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/grammar_base_fwd.hpp>
#include <sge/parse/json/grammar_fwd.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/parse/grammar_decl.hpp>

namespace sge::parse::json
{

class grammar : public sge::parse::json::grammar_base
{
  FCPPT_NONMOVABLE(grammar);

public:
  grammar();

  ~grammar();

private:
  base_type<sge::parse::json::null> null_;

  base_type<bool> bool_;

  base_type<sge::charconv::utf8_string> quoted_string_;

  base_type<sge::parse::json::array> array_;

  base_type<sge::parse::json::object> object_;

  base_type<sge::parse::json::value> value_;

  base_type<sge::parse::json::start> start_;
};

}

#endif
