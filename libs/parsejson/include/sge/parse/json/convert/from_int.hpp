//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_CONVERT_FROM_INT_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_INT_HPP_INCLUDED

#include <sge/parse/json/int_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json::convert
{

template <typename IntType>
sge::parse::json::int_type from_int(IntType const _value)
{
  static_assert(std::is_integral_v<IntType>, "IntType must be an integral type");

  return static_cast<sge::parse::json::int_type>(_value);
}

}

#endif
