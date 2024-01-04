//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/get_return_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

/// Searches for a member with the name @a name
/**
 * @throws member_not_found if the member is not found
 * @throws invalid_get if the member has a different type than T
*/
template <typename T, typename Arg>
sge::parse::json::get_return_type<T, Arg>
find_member_exn(fcppt::reference<Arg> const _members, sge::charconv::utf8_string const &_name)
{
  static_assert(std::is_same_v<std::remove_const_t<Arg>, sge::parse::json::member_map>);

  return sge::parse::json::get_exn<T>(sge::parse::json::find_member_value_exn(_members, _name));
}

}

#endif
