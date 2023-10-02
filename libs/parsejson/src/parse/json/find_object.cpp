//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/const_optional_object_ref.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/find_object.hpp>
#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_object_ref.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>

namespace
{

template <typename Object>
fcppt::optional::reference<Object>
find_object_impl(fcppt::reference<Object> const _input_object, sge::parse::json::path const &_path)
{
  using object_ref = fcppt::reference<Object>;

  using result_type = fcppt::optional::reference<Object>;

  object_ref current_object(_input_object);

  for (sge::charconv::utf8_string const &current_member : _path.get())
  {
    if (fcppt::optional::maybe(
            sge::parse::json::find_member_value(
                fcppt::make_ref(current_object.get().members), current_member),
            fcppt::const_(true),
            [&current_object, &current_member, &_path](auto const &_val)
            {
              current_object = object_ref(sge::parse::json::get_exn_message<Object>(
                  _val,
                  [&_path, &current_member]
                  {
                    return FCPPT_TEXT("Couldn't navigate to \"") +
                           sge::parse::json::detail::to_fcppt_string(
                               sge::parse::json::path_to_string(_path)) +
                           FCPPT_TEXT("\", stopped at \"") +
                           sge::parse::json::detail::to_fcppt_string(current_member);
                  }));

              return false;
            }))
    {
      return result_type();
    }
  }

  return result_type(current_object);
}

}

sge::parse::json::optional_object_ref sge::parse::json::find_object(
    fcppt::reference<sge::parse::json::object> const _input_object,
    sge::parse::json::path const &_path)
{
  return find_object_impl(_input_object, _path);
}

sge::parse::json::const_optional_object_ref sge::parse::json::find_object(
    fcppt::reference<sge::parse::json::object const> const _input_object,
    sge::parse::json::path const &_path)
{
  return find_object_impl(_input_object, _path);
}
