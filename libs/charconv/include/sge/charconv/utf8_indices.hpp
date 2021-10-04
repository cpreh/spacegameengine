//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_UTF8_INDICES_HPP_INCLUDED
#define SGE_CHARCONV_UTF8_INDICES_HPP_INCLUDED

#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/detail/symbol.hpp>


namespace sge::charconv
{

SGE_CHARCONV_DETAIL_SYMBOL
sge::charconv::index_vector
utf8_indices(
	sge::charconv::utf8_string const &
);

}

#endif
