//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_bytes.hpp>
#include <sge/charconv/utf8_char.hpp>
#include <fcppt/text.hpp>

unsigned sge::charconv::utf8_bytes(sge::charconv::utf8_char const _ch)
{
  if (
      // NOLINTNEXTLINE(hicpp-signed-bitwise)
      (_ch & 0x80) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      == 0)
  {
    return 1U;
  }

  if (
      // NOLINTNEXTLINE(hicpp-signed-bitwise)
      (_ch & 0xE0) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      == 0xC0 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  )
  {
    return 2U;
  }

  if (
      // NOLINTNEXTLINE(hicpp-signed-bitwise)
      (_ch & 0xF0) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      == 0xE0 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  )
  {
    return 3U;
  }

  if (
      // NOLINTNEXTLINE(hicpp-signed-bitwise)
      (_ch & 0xF8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      == 0xF0 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  )
  {
    return 4U;
  }

  throw sge::charconv::exception{FCPPT_TEXT("Invalid UTF-8 byte")};
}
