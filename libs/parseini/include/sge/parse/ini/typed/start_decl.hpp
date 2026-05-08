//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_START_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_START_DECL_HPP_INCLUDED

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/typed/duplicate_section.hpp>
#include <sge/parse/ini/typed/is_section.hpp>
#include <sge/parse/ini/typed/save_type.hpp>
#include <sge/parse/ini/typed/section_start_error_fwd.hpp>
#include <sge/parse/ini/typed/start_error_fwd.hpp>
#include <sge/parse/ini/typed/start_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/start_result_fwd.hpp>
#include <sge/parse/ini/typed/result_type.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of_v.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/map_elements.hpp>
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

template <typename Sections>
class start
{
  template <typename Parser>
  using make_is_optional =
      std::bool_constant<std::remove_cvref_t<fcppt::deref_type<Parser>>::is_optional>;

  template <typename Lambda, typename Parser>
  using make_type_impl = fcppt::mpl::if_<
      start::make_is_optional<Parser>,
      fcppt::optional::object<fcppt::mpl::apply<Lambda, Parser>>,
      fcppt::mpl::apply<Lambda, Parser>>;

  template <typename Parser>
  using make_result_type =
      start::make_type_impl<fcppt::mpl::lambda<sge::parse::ini::typed::result_type>, Parser>;

  template <typename Parser>
  using make_save_type =
      start::make_type_impl<fcppt::mpl::lambda<sge::parse::ini::typed::save_type>, Parser>;

  template <typename Lambda>
  using make_inner = fcppt::record::map_elements<
      Sections,
      fcppt::mpl::bind<Lambda, fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  using parser_types = fcppt::mpl::list::map<
      fcppt::record::element_vector<Sections>,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<std::remove_cvref_t>,
          fcppt::mpl::bind<
              fcppt::mpl::lambda<fcppt::deref_type>,
              fcppt::mpl::lambda<fcppt::record::element_to_type>>>>;

  template <typename Parser>
  using is_section_parser =
      sge::parse::ini::typed::is_section<std::remove_cvref_t<fcppt::deref_type<Parser>>>;
public:
  static_assert(fcppt::record::is_object<Sections>::value);

  static_assert(
      fcppt::mpl::list::all_of_v<parser_types, fcppt::mpl::lambda<start::is_section_parser>>);

  explicit start(Sections &&);

  using inner_result = start::make_inner<fcppt::mpl::lambda<start::make_result_type>>;

  using result_type = sge::parse::ini::typed::start_result<inner_result>;

  using save_type = start::make_inner<fcppt::mpl::lambda<start::make_save_type>>;

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::start_error, result_type>
  parse(sge::parse::ini::start const &) const;

  [[nodiscard]]
  sge::parse::ini::start save(save_type const &) const;
private:
  using section_map = std::unordered_map<std::string, sge::parse::ini::entry_vector>;

  [[nodiscard]]
  static
  fcppt::tuple::object<std::vector<sge::parse::ini::typed::duplicate_section>, section_map>
  make_map(sge::parse::ini::section_vector const &);

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::start_error, result_type>
  run_parsers(section_map const &) const;

  template <typename Label>
  [[nodiscard]] fcppt::either::object<
      sge::parse::ini::typed::section_start_error,
      make_result_type<fcppt::record::label_value_type<Sections, Label>>>
  parse_one(section_map const &, fcppt::reference<std::set<std::string>>, Label const &) const;

  Sections sections_;
};
template <typename Sections>
start(Sections &&) -> start<Sections>;
}

#endif
