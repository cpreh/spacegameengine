//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_START_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_START_IMPL_HPP_INCLUDED

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/typed/duplicate_section.hpp>
#include <sge/parse/ini/typed/missing_section_error.hpp>
#include <sge/parse/ini/typed/result_type.hpp>
#include <sge/parse/ini/typed/section_error.hpp>
#include <sge/parse/ini/typed/section_start_error.hpp>
#include <sge/parse/ini/typed/start_decl.hpp>
#include <sge/parse/ini/typed/start_error.hpp>
#include <sge/parse/ini/typed/start_result_impl.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/unused_sections.hpp>
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

template <typename Sections>
sge::parse::ini::typed::start<Sections>::start(Sections &&_sections)
    : sections_{std::move(_sections)}
{
}

template <typename Sections>
fcppt::either::object<
    sge::parse::ini::typed::start_error,
    typename sge::parse::ini::typed::start<Sections>::result_type>
sge::parse::ini::typed::start<Sections>::parse(sge::parse::ini::start const &_start) const
{
  fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_section>, section_map> const
      sections{start::make_map(_start.sections)};

  std::vector<sge::parse::ini::typed::duplicate_section> const &duplicates{
      fcppt::tuple::get<0U>(sections)};

  return duplicates.empty()
             ? this->run_parsers(fcppt::tuple::get<1U>(sections))
             : fcppt::either::make_failure<result_type>(sge::parse::ini::typed::start_error{
                   sge::parse::ini::typed::start_error::variant{duplicates}});
}

template <typename Sections>
fcppt::tuple::object<
    std::vector<sge::parse::ini::typed::duplicate_section>,
    // NOLINTNEXTLINE(readability-redundant-typename)
    typename sge::parse::ini::typed::start<Sections>::section_map>
sge::parse::ini::typed::start<Sections>::make_map(sge::parse::ini::section_vector const &_sections)
{
  return fcppt::algorithm::fold(
      _sections,
      fcppt::tuple::make(std::vector<sge::parse::ini::typed::duplicate_section>{}, section_map{}),
      [](sge::parse::ini::section const &_arg,
         fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_section>, section_map> &&_state)
      {
        fcppt::container::get_or_insert_result<sge::parse::ini::entry_vector const &> const result{
            fcppt::container::get_or_insert_with_result(
                fcppt::tuple::get<1U>(_state),
                _arg.name,
                [_arg](std::string const &) { return _arg.entries; })};

        if (!result.inserted())
        {
          // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
          fcppt::tuple::get<0U>(_state).push_back(
              sge::parse::ini::typed::duplicate_section{_arg.name});
        }

        return std::move(_state);
      });
}

template <typename Sections>
fcppt::either::object<
    sge::parse::ini::typed::start_error,
    typename sge::parse::ini::typed::start<Sections>::result_type>
sge::parse::ini::typed::start<Sections>::run_parsers(section_map const &_map) const
{
  using init_type = fcppt::record::map_elements<
      inner_result,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<fcppt::either::object>,
          fcppt::mpl::constant<sge::parse::ini::typed::section_start_error>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  std::set<std::string> used{};

  return fcppt::either::map(
      fcppt::either::map_failure(
          fcppt::either::sequence_all<fcppt::either::object<
              std::vector<sge::parse::ini::typed::section_start_error>,
              inner_result>>(
              fcppt::record::init<init_type>(
                  [&_map, &used, this]<typename Label, fcppt::either::object_concept Type>(
                      fcppt::record::element<Label, Type> const &)
                  { return this->parse_one(_map, fcppt::make_ref(used), Label{}); })),
          [](std::vector<sge::parse::ini::typed::section_start_error> &&_error)
          {
            return sge::parse::ini::typed::start_error{
                sge::parse::ini::typed::start_error::variant{std::move(_error)}};
          }),
      [&used, &_map](inner_result &&_result)
      {
        std::set<std::string> unused_sections{fcppt::container::set_difference(
            fcppt::container::key_set<std::set<std::string>>(_map), used)};

        return result_type{
            std::move(_result),
            fcppt::optional::make_if(
                !unused_sections.empty(),
                [&unused_sections]
                { return sge::parse::ini::typed::unused_sections{std::move(unused_sections)}; })};
      });
}

template <typename Sections>
template <typename Label>
fcppt::either::object<
    sge::parse::ini::typed::section_start_error,
    typename sge::parse::ini::typed::start<Sections>:: template make_result_type<
        fcppt::record::label_value_type<Sections, Label>>>
sge::parse::ini::typed::start<Sections>::parse_one(
    section_map const &_map, fcppt::reference<std::set<std::string>> const _used, Label const &) const
{
  using parser = fcppt::record::label_value_type<Sections, Label>;
  using parser_result = make_result_type<parser>;
  constexpr bool const optional_section = make_is_optional<parser>::value;

  std::string const &name{fcppt::deref(fcppt::record::get<Label>(this->sections_)).name()};

  return fcppt::optional::maybe(
      fcppt::container::find_opt_mapped(_map, name),
      [&name]() -> fcppt::either::object<sge::parse::ini::typed::section_start_error, parser_result>
      {
        FCPPT_USE(name);
        if constexpr (optional_section)
        {
          return fcppt::either::make_success<sge::parse::ini::typed::section_start_error>(
              parser_result{});
        }
        else
        {
          return fcppt::either::make_failure<parser_result>(
              sge::parse::ini::typed::section_start_error{
                  sge::parse::ini::typed::section_start_error::variant{
                      sge::parse::ini::typed::missing_section_error{name}}});
        }
      },
      [_used, &name, this](fcppt::reference<sge::parse::ini::entry_vector const> const _mapped)
          -> fcppt::either::object<sge::parse::ini::typed::section_start_error, parser_result>
      {
        _used->insert(name);
        return fcppt::either::bind(
            fcppt::either::map_failure(
                fcppt::deref(fcppt::record::get<Label>(this->sections_)).parse(_mapped.get()),
                [](sge::parse::ini::typed::section_error &&_inner)
                {
                  return sge::parse::ini::typed::section_start_error{
                      sge::parse::ini::typed::section_start_error::variant{std::move(_inner)}};
                }),
            [](sge::parse::ini::typed::result_type<parser> &&_result)
            {
              if constexpr (optional_section)
              {
                return fcppt::either::make_success<sge::parse::ini::typed::section_start_error>(
                    fcppt::optional::make(std::move(_result)));
              }
              else
              {
                return fcppt::either::make_success<sge::parse::ini::typed::section_start_error>(
                    std::move(_result));
              }
            });
      });
}

#endif
