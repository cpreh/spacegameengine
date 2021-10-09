//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_bytes.hpp>
#include <sge/charconv/utf8_indices.hpp>
#include <sge/charconv/utf8_string.hpp>

sge::charconv::index_vector sge::charconv::utf8_indices(sge::charconv::utf8_string const &_string)
{
  sge::charconv::index_vector result{0U};

  for (sge::charconv::utf8_string::const_iterator it(_string.begin()); it < _string.end();)
  {
    unsigned const bytes{sge::charconv::utf8_bytes(*it)};

    result.push_back(result.back() + bytes);

    it += bytes;
  }

  return result;
}
