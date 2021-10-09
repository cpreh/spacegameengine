//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_MAKE_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_MAKE_VALUE_HPP_INCLUDED

#include <sge/parse/json/value.hpp>
#include <sge/parse/json/value_variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename Type>
sge::parse::json::value make_value(Type &&_value)
{
  return sge::parse::json::value{sge::parse::json::value_variant{std::forward<Type>(_value)}};
}

}

#endif
