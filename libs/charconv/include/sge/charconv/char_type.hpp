//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_CHAR_TYPE_HPP_INCLUDED
#define SGE_CHARCONV_CHAR_TYPE_HPP_INCLUDED

#include <sge/charconv/encoding_fwd.hpp>
#include <sge/charconv/detail/char_type.hpp>


namespace sge
{
namespace charconv
{

template<
	sge::charconv::encoding Encoding
>
using
char_type
=
typename
sge::charconv::detail::char_type<
	Encoding
>::type;

}
}

#endif
