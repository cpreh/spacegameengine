//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/typed/entry.hpp>
#include <sge/parse/ini/typed/entry_type_error.hpp>
#include <sge/parse/ini/typed/section.hpp>
#include <sge/parse/ini/typed/section_error.hpp>
#include <sge/parse/ini/typed/unused_keys.hpp>
#include <sge/parse/ini/typed/required.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/record/comparison.hpp> // IWYU pragma: keep
#include <fcppt/record/make.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/tuple/comparison.hpp> // IWYU pragma: keep
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <set>
#include <string>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("parse_ini_typed_element", "[sge]")
{
  sge::parse::ini::typed::entry<int, sge::parse::ini::typed::required::yes> const entry{"test"};

  CHECK(
      entry.parse("42") ==
      fcppt::either::make_success<sge::parse::ini::typed::entry_type_error>(42));
  CHECK(
      entry.parse("abc") ==
      fcppt::either::make_failure<int>(sge::parse::ini::typed::entry_type_error{
          typeid(int), sge::parse::ini::entry_name{"test"}, sge::parse::ini::value{"abc"}}));
}

TEST_CASE("parse_ini_typed_section", "[sge]")
{
  FCPPT_RECORD_MAKE_LABEL(label1);
  FCPPT_RECORD_MAKE_LABEL(label2);

  sge::parse::ini::typed::section const section{
      "main",
      fcppt::record::make(
          label1{} =
              sge::parse::ini::typed::entry<int, sge::parse::ini::typed::required::yes>{"test1"},
          label2{} =
              sge::parse::ini::typed::entry<std::string, sge::parse::ini::typed::required::yes>{
                  "test2"})};

  CHECK(
      section.parse(
          sge::parse::ini::entry_vector{
              sge::parse::ini::entry{
                  sge::parse::ini::entry_name{"test1"}, sge::parse::ini::value{"42"}},
              sge::parse::ini::entry{
                  sge::parse::ini::entry_name{"test2"}, sge::parse::ini::value{"abc"}}}) ==
      fcppt::either::make_success<sge::parse::ini::typed::section_error>(fcppt::record::make(
          label1{} = 42,
          label2{} = std::string{"abc"},
          sge::parse::ini::typed::unused_keys{} =
              fcppt::tuple::make(std::string{"main"}, std::set<std::string>{}))));
}

// NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
