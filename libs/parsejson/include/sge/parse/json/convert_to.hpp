//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_CONVERT_TO_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_HPP_INCLUDED

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/is_iterable.hpp>
#include <fcppt/not.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace parse
{
namespace json
{

// TODO: Add a test for this. This code is probably broken.
template <typename T>
std::enable_if_t<
    std::is_same_v<T, sge::parse::json::object> || std::is_same_v<T, sge::parse::json::array> ||
        std::is_same_v<T, sge::parse::json::null> || std::is_same_v<T, std::string> ||
        std::is_same_v<T, bool>,
    sge::parse::json::value>
convert_to(T const &_value)
{
  return sge::parse::json::value(_value);
}

template <typename T>
std::enable_if_t<
    std::is_integral<T>::value && not std::is_same<T, bool>::value,
    sge::parse::json::value>
convert_to(T const &_value)
{
  return sge::parse::json::value(static_cast<sge::parse::json::int_type>(_value));
}

template <typename T>
std::enable_if_t<std::is_floating_point<T>::value, sge::parse::json::value>
convert_to(T const &_value)
{
  return sge::parse::json::value(static_cast<sge::parse::json::float_type>(_value));
}

// TODO: We could make a convert_to which converts from a tuple to a
// (heterogenous) array
template <typename T>
std::enable_if_t<
    sge::parse::json::detail::is_iterable<T>::value && fcppt::not_(std::is_same_v<T, std::string>),
    sge::parse::json::value>
convert_to(T const &_value)
{
  return sge::parse::json::value(fcppt::algorithm::map<sge::parse::json::array>(
      _value,
      [](typename T::value_type const &_arg) { return sge::parse::json::convert_to(_arg); }));
}

}
}
}

#endif
