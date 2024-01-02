//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CHARCONV_DETAIL_PP_ENCODINGS_HPP_INCLUDED
#define SGE_CHARCONV_DETAIL_PP_ENCODINGS_HPP_INCLUDED

#include <sge/charconv/encoding.hpp> // IWYU pragma: keep

#define SGE_CHARCONV_DETAIL_PP_ENCODINGS \
  (sge::charconv::encoding::utf8)(sge::charconv::encoding::utf16)(sge::charconv::encoding::utf32)( \
      sge::charconv::encoding::wchar)

#endif
