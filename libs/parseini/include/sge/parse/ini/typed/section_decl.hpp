//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_DECL_HPP_INCLUDED

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/typed/is_entry.hpp>
#include <sge/parse/ini/typed/section_error_fwd.hpp>
#include <sge/parse/ini/typed/section_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/result_type.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_vector.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/record/map_elements.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{

template <typename Entries>
class section
{
  template <typename Parser>
  static constexpr bool make_is_optional =
      std::remove_cvref_t<fcppt::deref_type<Parser>>::is_optional;

  template <typename Parser>
  using make_result_type = std::conditional_t<
      make_is_optional<Parser>,
      fcppt::optional::object<sge::parse::ini::typed::result_type<Parser>>,
      sge::parse::ini::typed::result_type<Parser>>;
public:
  static_assert(fcppt::record::is_object<Entries>::value);

  static_assert(fcppt::mpl::list::all_of<
                fcppt::mpl::list::map<
                    fcppt::record::element_vector<Entries>,
                    fcppt::mpl::lambda<fcppt::record::element_to_type>>,
                fcppt::mpl::bind<
                    fcppt::mpl::lambda<sge::parse::ini::typed::is_entry>,
                    fcppt::mpl::bind<
                        fcppt::mpl::lambda<std::remove_cvref_t>,
                        fcppt::mpl::lambda<fcppt::deref_type>>>>::value);

  section(std::string &&, Entries &&);

  using result_type = fcppt::record::map_elements<
      Entries,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<section::make_result_type>,
          fcppt::mpl::lambda<fcppt::record::element_to_type>>>;

  [[nodiscard]]
  fcppt::either::object<sge::parse::ini::typed::section_error, result_type>
  parse(sge::parse::ini::entry_vector const &) const;
private:
  std::string name_;

  Entries entries_;
};
template <typename Entries>
section(std::string, Entries &&) -> section<Entries>;
}

#endif
