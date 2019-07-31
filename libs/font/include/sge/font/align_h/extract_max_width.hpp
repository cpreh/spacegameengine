//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_ALIGN_H_EXTRACT_MAX_WIDTH_HPP_INCLUDED
#define SGE_FONT_ALIGN_H_EXTRACT_MAX_WIDTH_HPP_INCLUDED

#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/align_h/variant_fwd.hpp>
#include <sge/font/detail/symbol.hpp>


namespace sge
{
namespace font
{
namespace align_h
{

SGE_FONT_DETAIL_SYMBOL
sge::font::align_h::optional_max_width
extract_max_width(
	sge::font::align_h::variant const &
);

}
}
}

#endif
