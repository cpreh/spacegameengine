//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_file_to_fcppt_string_exn.hpp>
#include <sge/tests/charconv/test_data.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("charconv flake_config", "[sge]")
{
  fcppt::string const result(sge::charconv::utf8_file_to_fcppt_string_exn(
      std::filesystem::path(SGE_TESTS_CHARCONV_TEST_DATA) / "config.json"));

  CHECK_FALSE(result.empty());
}

FCPPT_CATCH_END
