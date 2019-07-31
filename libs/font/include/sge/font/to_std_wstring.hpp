//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_TO_STD_WSTRING_HPP_INCLUDED
#define SGE_FONT_TO_STD_WSTRING_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{

SGE_FONT_DETAIL_SYMBOL
std::wstring
to_std_wstring(
	sge::font::string const &
);

}
}

#endif
