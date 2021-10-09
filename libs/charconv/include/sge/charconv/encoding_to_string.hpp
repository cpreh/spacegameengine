//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CHARCONV_ENCODING_TO_STRING_HPP_INCLUDED
#define SGE_CHARCONV_ENCODING_TO_STRING_HPP_INCLUDED

#include <sge/charconv/encoding_fwd.hpp>
#include <sge/charconv/detail/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge::charconv
{

SGE_CHARCONV_DETAIL_SYMBOL
fcppt::string encoding_to_string(sge::charconv::encoding);

}

#endif
