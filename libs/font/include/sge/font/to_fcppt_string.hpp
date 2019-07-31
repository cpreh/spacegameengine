//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_TO_FCPPT_STRING_HPP_INCLUDED
#define SGE_FONT_TO_FCPPT_STRING_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/optional_string.hpp>


namespace sge
{
namespace font
{

SGE_FONT_DETAIL_SYMBOL
fcppt::optional_string
to_fcppt_string(
	sge::font::string const &
);

}
}

#endif
