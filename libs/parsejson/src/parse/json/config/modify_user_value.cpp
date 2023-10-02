//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/config/modify_user_value.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/container/get_or_insert_with_result.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

void sge::parse::json::config::modify_user_value(
    sge::parse::json::object const &structure_json,
    fcppt::reference<sge::parse::json::object> const user_json,
    sge::parse::json::path const &input_path,
    sge::parse::json::value const &new_value)
{
  if (input_path.get().empty())
  {
    throw sge::parse::json::exception{FCPPT_TEXT("Input path is empty.")};
  }

  sge::parse::json::value const &old_value{
      sge::parse::json::find_and_convert_member<sge::parse::json::value>(
          structure_json, input_path)};

  if (old_value.get().type_index() != new_value.get().type_index())
  {
    throw sge::parse::json::exception{
        FCPPT_TEXT("Error trying to update the user configuration node \"") +
        sge::parse::json::detail::to_fcppt_string(sge::parse::json::path_to_string(input_path)) +
        FCPPT_TEXT("\", the types of the old and new value didn't match. The old type was \"") +
        fcppt::from_std_string(
            fcppt::type_name_from_info(fcppt::variant::type_info(old_value.get()))) +
        FCPPT_TEXT("\", the new type was \"") +
        fcppt::from_std_string(
            fcppt::type_name_from_info(fcppt::variant::type_info(new_value.get())))};
  }

  sge::parse::json::object &target =
      // 0 is not permitted, 1 would mean: just take a value from
      // user_json, > 1 means: recursively make a path in the user_json
      input_path.get().size() > 1
          ? sge::parse::json::make_recursive_objects(
                user_json,
                // TODO(philipp): path::pop_back?
                sge::parse::json::path{sge::parse::json::path::sequence_type{
                    input_path.get().begin(), std::prev(input_path.get().end())}})
                .get()
          : user_json.get();

  auto const result{fcppt::container::get_or_insert_with_result(
      target.members,
      input_path.get().back(),
      [&new_value](sge::charconv::utf8_string const &) { return new_value; })};

  if (!result.inserted())
  {
    result.element() = fcppt::make_recursive(new_value);
  }
}
