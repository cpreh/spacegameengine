//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED

#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/get_return_type.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename T, typename Arg>
inline sge::parse::json::get_return_type<
    T,
    Arg>
get_exn(fcppt::reference< // NOLINT(readability-avoid-const-params-in-decls)
        Arg> const _val)
{
  static_assert(std::is_same_v<sge::parse::json::value, std::remove_const_t<Arg>>);

  return sge::parse::json::get_exn_message<T>(_val, [] { return fcppt::string{FCPPT_TEXT("")}; });
}

}

#endif
