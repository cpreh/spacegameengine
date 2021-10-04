//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_LOAD_OFFSET_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_LOAD_OFFSET_HPP_INCLUDED

#include <sge/font/vector_fwd.hpp>
#include <sge/parse/json/member_map.hpp>


namespace sge::font::bitmap::impl
{

sge::font::vector
load_offset(
	sge::parse::json::member_map const &
);

}

#endif
