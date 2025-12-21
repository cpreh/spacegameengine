//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_DECL_HPP_INCLUDED

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/typed/duplicate_entry.hpp>
#include <sge/parse/ini/typed/entry_error_fwd.hpp>
#include <sge/parse/ini/typed/is_entry.hpp>
#include <sge/parse/ini/typed/section_error_fwd.hpp>
#include <sge/parse/ini/typed/section_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/result_type.hpp>
#include <sge/parse/ini/typed/unused_keys.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of_v.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/record/disjoint_product.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/record/object_fwd.hpp>
#include <fcppt/tuple/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{

template <typename Entries>
class section
{
  template <typename Parser>
  using make_is_optional = std::bool_constant<Parser::is_optional>;

  template <typename Parser>
  using make_result_type = fcppt::mpl::if_<
      section::make_is_optional<Parser>,
      fcppt::optional::object<sge::parse::ini::typed::result_type<Parser>>,
      sge::parse::ini::typed::result_type<Parser>>;

  using parser_types = fcppt::mpl::list::map<
      fcppt::record::element_vector<Entries>,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<std::remove_cvref_t>,
          fcppt::mpl::bind<
              fcppt::mpl::lambda<fcppt::deref_type>,
              fcppt::mpl::lambda<fcppt::record::element_to_type>>>>;

  using inner_result = fcppt::record::map_elements<
      Entries,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<section::make_result_type>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;
public:
  static constexpr bool is_optional =
      fcppt::mpl::list::all_of_v<parser_types, fcppt::mpl::lambda<section::make_is_optional>>;

  static_assert(fcppt::record::is_object<Entries>::value);

  static_assert(fcppt::mpl::list::
                    all_of_v<parser_types, fcppt::mpl::lambda<sge::parse::ini::typed::is_entry>>);

  section(std::string &&, Entries &&);

  using result_type = fcppt::record::disjoint_product<
      inner_result,
      fcppt::record::object<fcppt::record::element<
          sge::parse::ini::typed::unused_keys,
          fcppt::tuple::object<std::string, std::set<std::string>>>>>;

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::section_error, result_type>
  parse(sge::parse::ini::entry_vector const &) const;
private:
  using string_map = std::unordered_map<std::string, std::string>;

  [[nodiscard]]
  static
  fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_entry>, string_map>
  make_map(sge::parse::ini::entry_vector const &);

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::section_error, result_type>
  run_parsers(string_map const &) const;

  template <typename Label>
  [[nodiscard]] fcppt::either::object<
      sge::parse::ini::typed::entry_error,
      make_result_type<fcppt::record::label_value_type<Entries, Label>>>
  parse_one(string_map const &, fcppt::reference<std::set<std::string>>, Label const &) const;

  std::string name_;

  Entries entries_;
};
template <typename Entries>
section(std::string, Entries &&) -> section<Entries>;
}

#endif
