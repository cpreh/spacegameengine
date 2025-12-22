//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_IMPL_HPP_INCLUDED

#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/typed/duplicate_entry.hpp>
#include <sge/parse/ini/typed/entry_error.hpp>
#include <sge/parse/ini/typed/entry_type_error.hpp>
#include <sge/parse/ini/typed/result_type.hpp>
#include <sge/parse/ini/typed/section_decl.hpp>
#include <sge/parse/ini/typed/section_error.hpp>
#include <sge/parse/ini/typed/section_result_impl.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/unused_entries.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop_break_record.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/map_record.hpp> // IWYU pragma: keep
#include <fcppt/container/get_or_insert_result.hpp>
#include <fcppt/container/get_or_insert_with_result.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/key_set.hpp>
#include <fcppt/container/set_difference.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/sequence_all.hpp>
#include <fcppt/either/object_concept.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/init.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

template <typename Entries>
sge::parse::ini::typed::section<Entries>::section(std::string &&_name, Entries &&_entries)
    : name_{std::move(_name)}, entries_{std::move(_entries)}
{
}

template <typename Entries>
fcppt::either::object<
    sge::parse::ini::typed::section_error,
    typename sge::parse::ini::typed::section<Entries>::result_type>
sge::parse::ini::typed::section<Entries>::parse(sge::parse::ini::entry_vector const &_entries) const
{
  fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_entry>, string_map> const
      entry_map{section::make_map(_entries)};

  std::vector<sge::parse::ini::typed::duplicate_entry> const &duplicates{
      fcppt::tuple::get<0U>(entry_map)};

  return duplicates.empty()
             ? this->run_parsers(fcppt::tuple::get<1U>(entry_map))
             : fcppt::either::make_failure<result_type>(sge::parse::ini::typed::section_error{
                   sge::parse::ini::typed::section_error::variant{duplicates}});
}

template <typename Entries>
fcppt::tuple::object<
    std::vector<sge::parse::ini::typed::duplicate_entry>,
    typename sge::parse::ini::typed::section<Entries>::string_map>
sge::parse::ini::typed::section<Entries>::make_map(sge::parse::ini::entry_vector const &_entries)
{
  return fcppt::algorithm::fold(
      _entries,
      fcppt::tuple::make(std::vector<sge::parse::ini::typed::duplicate_entry>{}, string_map{}),
      [](sge::parse::ini::entry const &_arg,
         fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_entry>, string_map> &&_state)
      {
        fcppt::container::get_or_insert_result<std::string const &> const result{
            fcppt::container::get_or_insert_with_result(
                fcppt::tuple::get<1U>(_state),
                _arg.name,
                [_arg](std::string const &) { return _arg.value; })};

        if (!result.inserted())
        {
          // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
          fcppt::tuple::get<0U>(_state).push_back(
              sge::parse::ini::typed::duplicate_entry{_arg.name});
        }

        return std::move(_state);
      });
}

template <typename Entries>
fcppt::either::object<
    sge::parse::ini::typed::section_error,
    typename sge::parse::ini::typed::section<Entries>::result_type>
sge::parse::ini::typed::section<Entries>::run_parsers(string_map const &_map) const
{
    using init_type = fcppt::record::map_elements<
        inner_result,
        fcppt::mpl::bind<
            fcppt::mpl::lambda<fcppt::either::object>,
            fcppt::mpl::constant<sge::parse::ini::typed::entry_error>,
            fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

    std::set<std::string> used{};

    return fcppt::either::map(
        fcppt::either::map_failure(
            fcppt::either::sequence_all<fcppt::either::object<
                std::vector<sge::parse::ini::typed::entry_error>,
                inner_result>>(
                fcppt::record::init<init_type>(
                    [&_map, &used, this]<typename Label, fcppt::either::object_concept Type>(
                        fcppt::record::element<Label, Type> const &)
                    { return this->parse_one(_map, fcppt::make_ref(used), Label{}); })),
            [](std::vector<sge::parse::ini::typed::entry_error> &&_error)
            {
              return sge::parse::ini::typed::section_error{
                  sge::parse::ini::typed::section_error::variant{std::move(_error)}};
            }),
        [&used, &_map, this](inner_result &&_result)
        {
          std::set<std::string> unused_entries{fcppt::container::set_difference(
              fcppt::container::key_set<std::set<std::string>>(_map), used)};

          return result_type{
              std::move(_result),
              fcppt::optional::make_if(
                  !unused_entries.empty(),
                  [&unused_entries, this]
                  {
                    return sge::parse::ini::typed::unused_entries{
                        sge::parse::ini::section_name{this->name_}, std::move(unused_entries)};
                  })};
        });
}

template <typename Entries>
template <typename Label>
fcppt::either::object<
    sge::parse::ini::typed::entry_error,
    typename sge::parse::ini::typed::section<Entries>:: template make_result_type<
        fcppt::record::label_value_type<Entries, Label>>>
sge::parse::ini::typed::section<Entries>::parse_one(
    string_map const &_map, fcppt::reference<std::set<std::string>> const _used, Label const &) const
{
  using parser = fcppt::record::label_value_type<Entries, Label>;
  using parser_result = make_result_type<parser>;
  constexpr bool const optional_entry = make_is_optional<parser>::value;

  std::string const &name{fcppt::deref(fcppt::record::get<Label>(this->entries_)).name()};

  return fcppt::optional::maybe(
      fcppt::container::find_opt_mapped(_map, name),
      [&name]() -> fcppt::either::object<sge::parse::ini::typed::entry_error, parser_result>
      {
        FCPPT_USE(name);
        if constexpr (optional_entry)
        {
          return fcppt::either::make_success<sge::parse::ini::typed::entry_error>(parser_result{});
        }
        else
        {
          return fcppt::either::make_failure<parser_result>(
              sge::parse::ini::typed::entry_error{sge::parse::ini::typed::entry_error::variant{
                  sge::parse::ini::typed::missing_entry_error{name}}});
        }
      },
      [_used, &name, this](fcppt::reference<std::string const> const _mapped)
          -> fcppt::either::object<sge::parse::ini::typed::entry_error, parser_result>
      {
        _used->insert(name);
        return fcppt::either::bind(
            fcppt::either::map_failure(
                fcppt::deref(fcppt::record::get<Label>(this->entries_)).parse(_mapped.get()),
                [](sge::parse::ini::typed::entry_type_error &&_inner)
                {
                  return sge::parse::ini::typed::entry_error{
                      sge::parse::ini::typed::entry_error::variant{std::move(_inner)}};
                }),
            [](sge::parse::ini::typed::result_type<parser> &&_result)
            {
              if constexpr (optional_entry)
              {
                return fcppt::either::make_success<sge::parse::ini::typed::entry_error>(
                    fcppt::optional::make(std::move(_result)));
              }
              else
              {
                return fcppt::either::make_success<sge::parse::ini::typed::entry_error>(
                    std::move(_result));
              }
            });
      });
}

#endif
