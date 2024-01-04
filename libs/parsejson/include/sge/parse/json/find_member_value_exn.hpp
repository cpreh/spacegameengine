//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get_return_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/member_not_found.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename Arg>
sge::parse::json::get_return_type<sge::parse::json::value, Arg>
find_member_value_exn(fcppt::reference<Arg> const _members, sge::charconv::utf8_string const &_name)
{
  static_assert(std::is_same_v<std::remove_const_t<Arg>, sge::parse::json::member_map>);

  return fcppt::optional::to_exception(
      sge::parse::json::find_member_value(_members, _name),
      [&_name]
      {
        return sge::parse::json::member_not_found(
            FCPPT_TEXT("Cannot find member \"") + sge::parse::json::detail::to_fcppt_string(_name) +
            FCPPT_TEXT("\" in a json object's member list!"));
      });
}

}

#endif
