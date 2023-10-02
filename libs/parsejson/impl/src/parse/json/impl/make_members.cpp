//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/impl/make_members.hpp>
#include <sge/parse/json/impl/member_vector.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/not.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/strong_typedef_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/container/insert.hpp>
#include <fcppt/container/make_move_range.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/try_call.hpp>
#include <fcppt/parse/custom_error.hpp>
#include <fcppt/parse/position.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_DECLARE_STRONG_TYPEDEF(sge::charconv::utf8_string, double_insert);

sge::parse::json::member_map make_members_impl(sge::parse::json::impl::member_vector &&_args)
{
  return fcppt::algorithm::fold(
      fcppt::container::make_move_range(std::move(_args)),
      sge::parse::json::member_map{},
      [](fcppt::tuple::object<sge::charconv::utf8_string, fcppt::recursive<sge::parse::json::value>>
             &&_element, // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
         sge::parse::json::member_map &&_state)
      {
        if (fcppt::not_(fcppt::container::insert(
                _state,
                sge::parse::json::member{
                    fcppt::tuple::get<0>(_element), std::move(fcppt::tuple::get<1>(_element))})))
        {
          throw // NOLINT(hicpp-exception-baseclass)
              double_insert{// NOLINT(hicpp-exception-baseclass)
                            std::move(fcppt::tuple::get<0>(_element))};
        }

        return std::move(_state);
      });
}

}

fcppt::either::object<fcppt::parse::custom_error<char>, sge::parse::json::member_map>
sge::parse::json::impl::make_members(
    fcppt::parse::position<char> const _pos, sge::parse::json::impl::member_vector &&_args)
{
  return fcppt::either::try_call<double_insert>(
      [&_args] { return make_members_impl(std::move(_args)); },
      [_pos](double_insert const &_error)
      {
        return fcppt::parse::custom_error<char>{
            _pos, std::string{"Duplicate object name: "} + _error.get()};
      });
}
