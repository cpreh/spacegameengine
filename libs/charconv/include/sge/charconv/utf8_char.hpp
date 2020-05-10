//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_UTF8_CHAR_HPP_INCLUDED
#define SGE_CHARCONV_UTF8_CHAR_HPP_INCLUDED

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/encoding.hpp>


namespace sge
{
namespace charconv
{

using
utf8_char
=
sge::charconv::char_type<
	sge::charconv::encoding::utf8
>;

}
}

#endif
