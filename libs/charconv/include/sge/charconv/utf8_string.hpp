//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_UTF8_STRING_HPP_INCLUDED
#define SGE_CHARCONV_UTF8_STRING_HPP_INCLUDED

#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>


namespace sge
{
namespace charconv
{

using
utf8_string
=
sge::charconv::string_type<
	sge::charconv::encoding::utf8
>;

}
}

#endif
