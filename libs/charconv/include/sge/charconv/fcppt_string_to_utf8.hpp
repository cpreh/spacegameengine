//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_FCPPT_STRING_TO_UTF8_HPP_INCLUDED
#define SGE_CHARCONV_FCPPT_STRING_TO_UTF8_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace charconv
{

SGE_CHARCONV_DETAIL_SYMBOL
sge::charconv::utf8_string
fcppt_string_to_utf8(
	fcppt::string const &
);

}
}

#endif
