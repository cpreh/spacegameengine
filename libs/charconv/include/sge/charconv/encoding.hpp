//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CHARCONV_ENCODING_HPP_INCLUDED
#define SGE_CHARCONV_ENCODING_HPP_INCLUDED

#include <sge/charconv/encoding_fwd.hpp>

namespace sge::charconv
{

enum class encoding
{
  utf8,
  utf16,
  utf32,
  wchar,
  fcppt_maximum = wchar
};

}

#endif
