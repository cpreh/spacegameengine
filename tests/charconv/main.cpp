//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/tests/charconv/test_data.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/mpl/list/enum_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("charconv", "[sge]")
{
  std::filesystem::path const test_data_path(
      std::filesystem::path(SGE_TESTS_CHARCONV_TEST_DATA) / "test_data.txt");

  std::ifstream stream(test_data_path);

  REQUIRE(stream.is_open());

  std::stringstream stringstream;

  stringstream << stream.rdbuf();

  std::string const input(stringstream.str());

  fcppt::algorithm::loop(
      fcppt::mpl::list::enum_range<sge::charconv::encoding>{},
      [&input](auto const _dest_encoding)
      {
        FCPPT_USE(_dest_encoding);

        using dest_encoding = fcppt::tag_type<decltype(_dest_encoding)>;

        auto const result(
            sge::charconv::convert<dest_encoding::value, sge::charconv::encoding::utf8>(input));

        std::string const back(
            sge::charconv::convert<sge::charconv::encoding::utf8, dest_encoding::value>(result));

        CHECK(input == back);
      });
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
