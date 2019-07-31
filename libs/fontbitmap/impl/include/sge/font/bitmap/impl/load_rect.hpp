//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_LOAD_RECT_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_LOAD_RECT_HPP_INCLUDED

#include <sge/image2d/rect_fwd.hpp>
#include <sge/parse/json/member_map.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{
namespace impl
{

sge::image2d::rect
load_rect(
	sge::parse::json::member_map const &
);

}
}
}
}

#endif
