//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/config/merge_trees.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/key_set.hpp>
#include <fcppt/container/set_union.hpp>
#include <fcppt/optional/combine.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>

namespace
{

struct visitor
{
  using result_type = sge::parse::json::value;

  result_type operator()(
      sge::parse::json::object const &_original, sge::parse::json::object const &_update) const
  {
    return sge::parse::json::make_value(sge::parse::json::config::merge_trees(_original, _update));
  }

  template <typename T1, typename T2>
  result_type operator()(T1 const &, T2 const &_update) const
  {
    return sge::parse::json::make_value(_update);
  }
};

}

sge::parse::json::object sge::parse::json::config::merge_trees(
    sge::parse::json::object const &_original, sge::parse::json::object const &_update)
{
  using string_set = std::set<sge::charconv::utf8_string>;

  return sge::parse::json::object(fcppt::algorithm::map_optional<sge::parse::json::member_map>(
      fcppt::container::set_union(
          fcppt::container::key_set<string_set>(_original.members),
          fcppt::container::key_set<string_set>(_update.members)),
      [&_original, &_update](sge::charconv::utf8_string const &_key)
      {
        return fcppt::optional::map(
            fcppt::optional::combine(
                fcppt::optional::copy_value(
                    sge::parse::json::find_member_value(fcppt::make_cref(_original.members), _key)),
                fcppt::optional::copy_value(
                    sge::parse::json::find_member_value(fcppt::make_cref(_update.members), _key)),
                [](sge::parse::json::value const &_original_value,
                   sge::parse::json::value const &_update_value) {
                  return fcppt::variant::apply(
                      visitor{}, _original_value.get(), _update_value.get());
                }),
            [&_key](sge::parse::json::value const &_combined)
            { return sge::parse::json::member(_key, _combined); });
      }));
}
