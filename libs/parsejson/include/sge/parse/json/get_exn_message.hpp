//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_GET_EXN_MESSAGE_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_EXN_MESSAGE_HPP_INCLUDED

#include <sge/parse/json/get_return_type.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/to_optional_ref.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <typeinfo> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename Type, typename Arg, typename MakeMessage>
sge::parse::json::get_return_type<Type, Arg>
get_exn_message(fcppt::reference<Arg> const _val, MakeMessage const &_make_message)
{
  static_assert(std::is_same_v<std::remove_const_t<Arg>, sge::parse::json::value>);

  return fcppt::optional::to_exception(
      fcppt::variant::to_optional_ref<std::conditional_t<std::is_const_v<Arg>, Type const, Type>>(
          _val.get().get()),
      [&_val, &_make_message]
      {
        return sge::parse::json::invalid_get(
            FCPPT_TEXT("json::get_exn<") +
            fcppt::from_std_string(fcppt::type_name_from_info(typeid(Type))) +
            FCPPT_TEXT("> failed! Type is \"") +
            fcppt::from_std_string(
                fcppt::type_name_from_info(fcppt::variant::type_info(_val.get().get()))) +
            FCPPT_TEXT("\" instead! Additional information: ") + _make_message());
      });
}

}

#endif
