//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/parse_string.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/convert.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/comparison.hpp>
#include <fcppt/parse/make_parse_string_success.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>
#include <string>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace Catch
{

template <>
struct StringMaker<sge::parse::ini::start>
{
  static std::string convert(sge::parse::ini::start const &_value)
  {
    return fcppt::catch_::convert(_value.sections);
  }
};

template <>
struct StringMaker<sge::parse::ini::section>
{
  static std::string convert(sge::parse::ini::section const &_value)
  {
    return fcppt::catch_::convert(std::make_tuple(_value.name, _value.entries));
  }
};

template <>
struct StringMaker<sge::parse::ini::entry>
{
  static std::string convert(sge::parse::ini::entry const &_value)
  {
    return fcppt::catch_::convert(std::make_tuple(_value.name, _value.value));
  }
};

}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("parse_ini", "[sge]")
{
  CHECK(
      sge::parse::ini::parse_string(std::string{"[section]\n"
                                                "foo1 = bar1\n"
                                                "[sectionfoo]\n"
                                                "foo3 = bar3\n"
                                                "foo4=bar4\n"
                                                "\n"
                                                "empty=\n"}) ==
      fcppt::parse::make_parse_string_success<char>(
          sge::parse::ini::start{sge::parse::ini::section_vector{
              sge::parse::ini::section{
                  sge::parse::ini::section_name{std::string{"section"}},
                  sge::parse::ini::entry_vector{sge::parse::ini::entry{
                      sge::parse::ini::entry_name{std::string{"foo1"}},
                      sge::parse::ini::value{std::string{"bar1"}}}}},
              sge::parse::ini::section{
                  sge::parse::ini::section_name{std::string{"sectionfoo"}},
                  sge::parse::ini::entry_vector{
                      sge::parse::ini::entry{
                          sge::parse::ini::entry_name{std::string{"foo3"}},
                          sge::parse::ini::value{std::string{"bar3"}}},
                      sge::parse::ini::entry{
                          sge::parse::ini::entry_name{std::string{"foo4"}},
                          sge::parse::ini::value{std::string{"bar4"}}},
                      sge::parse::ini::entry{
                          sge::parse::ini::entry_name{std::string{"empty"}},
                          sge::parse::ini::value{std::string{}}}}}}}));
}

TEST_CASE("parse_ini error", "[sge]")
{
  CHECK(sge::parse::ini::parse_string(std::string{"garbage"}).has_failure());

  CHECK(sge::parse::ini::parse_string(std::string{"[foo] missing_newline"}).has_failure());

  CHECK(sge::parse::ini::parse_string(std::string{"[foo]\n invalid name=foo"}).has_failure());
}

// NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
